// standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// external libraries
#include <SDL2/SDL.h>

// internal headers
#include <engine/e_sdl.h>
#include <engine/e_input.h>
#include <engine/e_object_data.h>
#include <engine/e_scripting.h>
#include <project/p_render.h>
#include <project/p_world.h>

int main (int argc, char ** argv) {
  e_scripting_context_t scripting_context = e_scripting_create_context(16384);
  e_scripting_register_cfuncs(&scripting_context);
  
  e_input_initialize_state();
  printf("Compiled on %s @ %s\n", __DATE__, __TIME__);
  e_sdl_context_t sdl_context = e_sdl_setup("Nocturne Island Alpha", 640, 512, SDL_INIT_VIDEO);
  e_sdl_texture_atlas_t texture_atlas;
  p_render_load_atlas(&sdl_context, &texture_atlas, "assets/atlas.bmp");
  p_render_atlas_coord_t coord = {
    0, 0, 16, 16, 0
  };
  
  //load object_data definitions  
  e_object_data_def_initialize(256);
  e_scripting_run_script(scripting_context.context, "assets/scripts/objs.fe");
  p_world_data_init(16, 16, 16);
  p_world_data_t * world_data = p_world_data_get_all();
  
  // main event loop
  bool should_quit = false;
  while (!should_quit) {
    e_sdl_redraw(&sdl_context);
        
    e_input_handle();
        
    should_quit = e_input_get_state().should_quit;
    if (should_quit){
      printf("Closing...\n");
      break;
    }

    p_render_world_data(&sdl_context, &texture_atlas, world_data);
  }
  
  // DO NOT COMMENT OUT. MEMORY LEAK: FIX
  p_world_data_free();
  e_object_data_object_def_free();

  p_render_free_atlas(&texture_atlas);
  e_sdl_quit(&sdl_context);
  e_scripting_free_context(&scripting_context);
  return 0;
}
