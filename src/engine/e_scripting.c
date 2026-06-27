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

// external libraries
#include <libs/fe/fe.h>

// internal headers
#include <engine/e_scripting.h>
#include <engine/e_debug.h>
#include <engine/e_world_data.h>

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

void e_scripting_run_script (e_scripting_context_t * context, char * path) {
  FILE * file_ptr = fopen(path, "rb");
  if (file_ptr == NULL) {
    e_debug_script_not_found(path);
    return;
  }

  int gc = fe_savegc(context->context);
  
  while (true) {
    fe_Object * obj = fe_readfp(context->context, file_ptr);

    if (!obj) {
      break;
    }
    
    fe_eval(context->context, obj);
    fe_restoregc(context->context, gc);
  }

  fclose(file_ptr);
}

static fe_Object * e_loader_script_register_object_def (fe_Context * context, fe_Object * args) {
  int id = fe_tonumber(context, fe_nextarg(context, &args));
  e_world_object_type_e type = fe_tonumber(context, fe_nextarg(context, &args));
  int status = 0; // return status of object registration
  return fe_number(context, status);
}

void e_scripting_register_cfuncs (e_scripting_context_t * context) {
  fe_set(context->context,
	 fe_symbol(context->context, "register-obj"),
	 fe_cfunc(context->context, e_loader_script_register_object_def));
}
