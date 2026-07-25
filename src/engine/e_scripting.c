// e_scripting.c
// handles embedding of fe scripting language
// 
// 
// created: 26/06/2026

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

// external libraries
#include <libs/fe/fe.h>

// internal headers
#include <engine/e_scripting.h>
#include <engine/e_debug.h>
#include <engine/e_object_data.h>

e_scripting_context_t e_scripting_create_context(size_t memory_block_size) {
  e_scripting_context_t output_context;

  // do not allow memory block to be smaller than 8 kilobytes
  int bounded_block_size = fmax(memory_block_size, 8192);
  output_context.memory_block_size = bounded_block_size;
  output_context.memory_block = malloc(bounded_block_size);
  
  fe_Context * context = fe_open(output_context.memory_block, bounded_block_size);

  output_context.context = context;

  return output_context;
}

void e_scripting_free_context(e_scripting_context_t * context) {
  fe_close(context->context);
  free(context->memory_block);
}

void e_scripting_run_script (fe_Context * context, char * path) {
  FILE * file_ptr = fopen(path, "rb");
  if (file_ptr == NULL) {
    e_debug_script_not_found(path);
    return;
  }

  int gc = fe_savegc(context);
  
  while (true) {
    fe_Object * obj = fe_readfp(context, file_ptr);

    if (!obj) {
      break;
    }
    
    fe_eval(context, obj);
    fe_restoregc(context, gc);
  }

  fclose(file_ptr);
}

static fe_Object * e_scripting_cfunc_register_object_def (fe_Context * context, fe_Object * args) {
  char obj_name[256] = "";
  fe_tostring(context, fe_nextarg(context, &args), obj_name, 256);
  e_object_data_type_e type = fe_tonumber(context, fe_nextarg(context, &args));
  char callback_name[256] = "";
  fe_tostring(context, fe_nextarg(context, &args), callback_name, 256);
  int id = fe_tonumber(context, fe_nextarg(context, &args)); 
    
  // create registration for object def
  e_object_data_t object_info = {
    obj_name,
    type,
    fe_symbol(context, callback_name),
    id,
    id
  };
  
  int status = e_object_data_def_register(id, object_info);
  e_object_data_set_object_def(&object_info, id);
  
  return fe_number(context, status);
}

static fe_Object * e_scripting_cfunc_import_directive (fe_Context * context, fe_Object * args) {
  char file_name[256] = "";
  char * file_ext = malloc(8);
  int status = 0;
  fe_tostring(context, fe_nextarg(context, &args), file_name, 256);

  // check to make sure that the passed filename is a .fe file
  for (int ch = 0 ; ch < 256 ; ch++) {
    if (file_name[ch] != '.') {
      continue;
    }
    strncpy(file_ext, &file_name[ch], 8);
    break;
  }

  // if not correct file extension, exit
  if (strcmp(file_ext, ".fe")) {
    free(file_ext);
    e_debug_script_file_not_script(file_name);
    return fe_number(context, 1);
  }
  
  free(file_ext);
  
  e_scripting_run_script(context, file_name);
  
  return fe_number(context, status);
}

static fe_Object * e_scripting_cfunc_obj_callback (fe_Context * context, fe_Object * args) {
  int id = fe_tonumber(context, fe_nextarg(context, &args));
  int interact_type = fe_tonumber(context, fe_nextarg(context, &args));
  
  int gc = fe_savegc(context);
  fe_Object * callback_eval[2];
  callback_eval[0] = e_object_data_get_object_def(id)->callback;
  callback_eval[1] = fe_number(context, interact_type);

  fe_eval(context, fe_list(context, callback_eval, 2));

  fe_restoregc(context, gc);
   
  return fe_number(context, 0);
}

static fe_Object * e_scripting_cfunc_modulo (fe_Context * context, fe_Object * args) {
  int a = fe_tonumber(context, fe_nextarg(context, &args));
  int b = fe_tonumber(context, fe_nextarg(context, &args));
  int result = a % b;
  return fe_number(context, result);
}

void e_scripting_register_cfuncs (e_scripting_context_t * context) {

  fe_set(context->context,
	 fe_symbol(context->context, "register-obj"),
	 fe_cfunc(context->context, e_scripting_cfunc_register_object_def));

  fe_set(context->context,
	 fe_symbol(context->context, "import"),
	 fe_cfunc(context->context, e_scripting_cfunc_import_directive));

  fe_set(context->context,
	 fe_symbol(context->context, "callback-obj"),
	 fe_cfunc(context->context, e_scripting_cfunc_obj_callback));

  fe_set(context->context,
  	 fe_symbol(context->context, "mod"),
  	 fe_cfunc(context->context, e_scripting_cfunc_modulo));
}
