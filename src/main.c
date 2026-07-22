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

  // load world_data object definitions
  //int object_def_load_status;b
  e_world_object_t * object_definition_array;
  
  //object_def_load_status = e_loader_source_object_defs(&object_definition_array, 1, 256);
  //e_scripting_run_script(&scripting_context, "assets/scripts/test.fe");
  e_scripting_run_script(scripting_context.context, "assets/scripts/objs.fe");
  /*if (object_def_load_status > 0 || object_definition_array == NULL) {
    e_sdl_quit(&context);
    exit(object_def_load_status);
  }
  */
    
  // setup world data
  // note: come up with more memory safe way of allocating. maybe contexts?
  int world_data_init_status;
  e_world_object_t * world_data_array;
  world_data_init_status = e_world_data_initialize(&world_data_array, 10, 10, 10);
  if (world_data_init_status > 0 || world_data_array == NULL) {
    e_sdl_quit(&context);      
	
    exit(world_data_init_status);
  }
    
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
  free(world_data_array);
			  
  e_sdl_quit(&context);
  e_scripting_free_context(&scripting_context);
  return 0;
}
