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