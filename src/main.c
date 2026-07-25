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
#include <engine/e_scripting.h>

int main (int argc, char ** argv) {
  e_scripting_context_t scripting_context = e_scripting_create_context(16384);
  e_scripting_register_cfuncs(&scripting_context);
  
  e_input_initialize_state();
  printf("Compiled on %s @ %s\n", __DATE__, __TIME__);
  e_sdl_context_t context = e_sdl_setup("Nocturne Island Alpha", 640, 480, SDL_INIT_VIDEO);

  //load world_data object definitions  
  e_world_data_object_def_initialize(256);
  e_scripting_run_script(scripting_context.context, "assets/scripts/objs.fe");
        
  // main event loop
  bool should_quit = false;
  while (!should_quit) {
    e_sdl_redraw(&context);
        
    e_input_handle();
        
    should_quit = e_input_get_state().should_quit;
    if (should_quit){
      printf("Closing...\n");
      break;
    }	
    // insert gameplay loop here
  }

  // DO NOT COMMENT OUT. MEMORY LEAK: FIX
  e_world_data_object_def_free();
			  
  e_sdl_quit(&context);
  e_scripting_free_context(&scripting_context);
  return 0;
}
