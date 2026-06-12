// standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// external libraries
#include <SDL2/SDL.h>

// internal headers
#include <engine/e_sdl.h>
#include <engine/e_input.h>
#include <engine/e_world_data.h>

int main (int argc, char ** argv) {
    e_input_initialize_state();
    
    e_sdl_context_t context = e_sdl_setup("Nocturne Island Alpha", 640, 480, SDL_INIT_VIDEO);

    // setup world data
    // note: come up with more memory safe way of allocating. maybe contexts?
    e_world_object_t * world_data_array;
    e_world_data_initialize(&world_data_array, 10, 10, 10);
    
    // main event loop
    bool should_quit = false;
    while (!should_quit) {
        e_sdl_redraw(&context);
        
        e_input_handle();
        
        should_quit = e_input_get_state().should_quit;
        if (should_quit){
	  printf("%s\n", world_data_array[0].name);
	  break;
        }	
        // insert gameplay loop here
    }

    // DO NOT COMMENT OUT. MEMORY LEAK: FIX
    free(world_data_array);
			  
    e_sdl_quit(&context);
    return 0;
}
