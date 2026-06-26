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
