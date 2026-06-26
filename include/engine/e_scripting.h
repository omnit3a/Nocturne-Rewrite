// e_scripting.h
// created: 26/06/2026

#ifndef E_SCRIPTING_H_
#define E_SCRIPTING_H_

// external libraries
#include <libs/fe/fe.h>

typedef struct e_scripting_context_s {
  fe_Context * context;
  size_t memory_block_size;
  void * memory_block;
} e_scripting_context_t;

// MAKE SURE THAT ONLY UNINITIALIZED MEMORY IS PASSED FOR `void ** memory_block`
e_scripting_context_t e_scripting_create_context (size_t memory_block_size);
void e_scripting_free_context (e_scripting_context_t * context);

void e_scripting_run_script (e_scripting_context_t * context, char * path);

#endif
