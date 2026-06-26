#ifndef ENGINE_DEBUG_H_
#define ENGINE_DEBUG_H_

// standard library
#include <stdio.h>
#include <unistd.h>

// debuggable sub-systems
#define E_DEBUG_SUBSYSTEM_SDL "SDL2"
#define E_DEBUG_SUBSYSTEM_WORLD_DATA "WORLD_DATA"
#define E_DEBUG_SUBSYSTEM_LOAD_OBJECT_DEFS "LOAD_OBJECT_DEFS"
#define E_DEBUG_SUBSYSTEM_SCRIPTING "SCRIPTING"

// used for printing the status of an initialization sequence
// `stage` is the current stage of the sequence, `steps` is the amount of stages in the sequence
void e_debug_init_sequence_failure (char * subsystem, int stage, int steps, char * specifics);

// always returns `stage + 1`, except under the following conditions:
// 1. `stage + steps == 2` AKA when there is only one stage in a sequence
// 2. `stage > steps`
// under both of these conditions, "DONE" is printed instead of the current stage
int e_debug_init_sequence_success (char * subsystem, int stage, int steps, char * specifics);

// used in the case that something is already initialized
void e_debug_already_initialized (char * subsystem, char * specifics); 

// self-explanitory
void e_debug_script_not_found (char * script_name);

#endif
