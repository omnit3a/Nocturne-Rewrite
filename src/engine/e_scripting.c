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
    fclose(file_ptr);
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
  char init_callback_name[256] = "";
  fe_tostring(context, fe_nextarg(context, &args), init_callback_name, 256);
  char interact_callback_name[256] = "";
  fe_tostring(context, fe_nextarg(context, &args), interact_callback_name, 256);
  int id = fe_tonumber(context, fe_nextarg(context, &args));
    
  // create registration for object def
  e_object_data_t object_info = {
    obj_name,
    type,
    fe_symbol(context, init_callback_name),
    fe_symbol(context, interact_callback_name),
    NULL,
    id,
    id
  };

  object_info.id = id;
  
  int status = e_object_data_def_register(id, object_info);
  e_object_data_set_object_def(&object_info, id);
  // report to the user that the object was registered
  e_debug_script_registered_obj_def(&object_info);

  int gc = fe_savegc(context);
  fe_Object * init_callback_eval[2];
  // run initialization callback
  init_callback_eval[0] = e_object_data_get_object_def(id)->init_callback;
  init_callback_eval[1] = fe_number(context, id);
  fe_eval(context, fe_list(context, init_callback_eval, 2));
  fe_restoregc(context, gc);
  
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

static fe_Object * e_scripting_cfunc_obj_interact_callback (fe_Context * context, fe_Object * args) {
  int id = fe_tonumber(context, fe_nextarg(context, &args));
  int interact_type = fe_tonumber(context, fe_nextarg(context, &args));
  
  int gc = fe_savegc(context);
  fe_Object * callback_eval[2];
  // create function call out of callback and interaction type
  callback_eval[0] = e_object_data_get_object_def(id)->interact_callback;
  callback_eval[1] = fe_number(context, interact_type);

  fe_eval(context, fe_list(context, callback_eval, 2));

  fe_restoregc(context, gc);
   
  return fe_number(context, 0);
}

static fe_Object * e_scripting_cfunc_obj_set_field (fe_Context * context, fe_Object * args) {
  e_object_data_fields_e field_id = fe_tonumber(context, fe_nextarg(context, &args));
  int id = fe_tonumber(context, fe_nextarg(context, &args));

  e_object_data_t * temp_obj = e_object_data_get_object_def(id);

  switch (field_id) {
    case FI_SIZE:
      temp_obj->size = fe_tonumber(context, fe_nextarg(context, &args));
      break;
    case FI_VOLUME:
      temp_obj->volume = fe_tonumber(context, fe_nextarg(context, &args));
      break;
    case FI_GRAVITY:
      temp_obj->physics.gravity = fe_tonumber(context, fe_nextarg(context, &args));
      break;
    case FI_FLOW:
      temp_obj->physics.as_non_solid.flow = fe_tonumber(context, fe_nextarg(context, &args));
      break;
    case FI_DISPERSAL:
      temp_obj->physics.as_non_solid.dispersal = fe_tonumber(context, fe_nextarg(context, &args));
      break;
    case FI_IS_SOLID:
      temp_obj->physics.is_solid = (fe_tonumber(context, fe_nextarg(context, &args)) >= 1);
      break;
    case FI_HARDNESS:
      temp_obj->physics.hardness = fe_tonumber(context, fe_nextarg(context, &args));
      break;
    case FI_TEXTURE:
      temp_obj->texture_uv = fe_tonumber(context, fe_nextarg(context, &args));
      break;
    case FI_PHYSICS:
      char physics_callback_name[256] = "";
      fe_tostring(context, fe_nextarg(context, &args), physics_callback_name, 256);
      temp_obj->physics_callback = fe_symbol(context, physics_callback_name);
      break;
    default:
      // TODO: Add error handling for this
      printf("Unrecognized field-id: %d\n", field_id);
      break;
  }

  e_object_data_set_object_def(temp_obj, id);
  temp_obj = e_object_data_get_object_def(id);

  return fe_number(context, 0);
}

// fe doesnt have built-in modulo operator for some reason, so i added this.
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
	 fe_symbol(context->context, "obj-interact-callback"),
	 fe_cfunc(context->context, e_scripting_cfunc_obj_interact_callback));

  fe_set(context->context,
	 fe_symbol(context->context, "set-obj-field"),
	 fe_cfunc(context->context, e_scripting_cfunc_obj_set_field));

  fe_set(context->context,
  	 fe_symbol(context->context, "mod"),
  	 fe_cfunc(context->context, e_scripting_cfunc_modulo));
}
