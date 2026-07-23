// e_debug.c
// used for logging
// 
// 
// created: 11/06/2026

// standard library
#include <stdio.h>
#include <stdlib.h>

// internal headers
#include <engine/e_debug.h>

void e_debug_init_sequence_failure (char * subsystem, int stage, int steps, char * specifics) {
    fprintf(stderr, "[%s - INIT] × (%d/%d): Failed to initialize %s\n", subsystem, stage, steps, specifics);
}

int e_debug_init_sequence_success (char * subsystem, int stage, int steps, char * specifics) {
    if (stage > steps || stage + steps == 2) {
        fprintf(stdout, "[%s - INIT] DONE\t: %s\n", subsystem, specifics);
        return stage;
    }
    
    fprintf(stdout, "[%s - INIT] ✓ (%d/%d)\t: %s\n", subsystem, stage, steps, specifics);
    
    return stage + 1;
}

void e_debug_already_initialized (char * subsystem, char * specifics) {
  if (specifics != NULL) { 
    fprintf(stderr, "[%s - STATUS]: Already initialized: %s\n", subsystem, specifics);
    return;
  }

  fprintf(stderr, "[%s - STATUS]: Already initialized\n", subsystem);
}

void e_debug_script_not_found (char * script_name) {
  if (script_name != NULL) {
    fprintf(stderr, "[%s - STATUS]: %s\t: Could not find script\n", E_DEBUG_SUBSYSTEM_SCRIPTING, script_name);
    return;
  }

  fprintf(stderr, "Why TF are you reporting that you couldn't load a script if you're not even gonna specify which one\n");
}

void e_debug_script_file_not_script (char * script_name) {
  fprintf(stderr, "[%s - STATUS]: \'%s\'\t: File is not a \'.fe\' file\n", E_DEBUG_SUBSYSTEM_SCRIPTING, script_name);
  return;
}
