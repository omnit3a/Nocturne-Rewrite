// standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// external libraries
#include <SDL2/SDL.h>

// internal headers
#include <engine/e_sdl.h>
#include <engine/e_input.h>

int main (int argc, char ** argv) {
    e_sdl_context_t context = e_sdl_setup("Nocturne Island Alpha", 640, 480, SDL_INIT_VIDEO);
    e_input_initialize_state();
    
    // main event loop
    bool should_quit = false;
    while (!should_quit) {
        e_sdl_redraw(&context);
        
        e_input_handle();
        
        // remove e_input_print_state() from main loop when done adding input system
        e_input_print_state();
        
        should_quit = e_input_get_state().should_quit;
        if (should_quit){
            break;
        }
        
        // insert gameplay loop here
    }
    
    e_sdl_quit(&context);
    return 0;
}