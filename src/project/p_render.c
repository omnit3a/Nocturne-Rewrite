// p_render.c
// handles rendering of the game, seperated from the engine
// 
// 
// created: 25/07/2026

// standard library
#include <stdio.h>
#include <stdlib.h>

// external libraries
#include <SDL2/SDL.h>

// internal headers
#include <engine/e_sdl.h>
#include <engine/e_debug.h>
#include <project/p_render.h>

int p_render_load_atlas(e_sdl_context_t * sdl_context, e_sdl_texture_atlas_t * atlas, char * atlas_path) {
  FILE * file_ptr = fopen(atlas_path, "r");
  if (file_ptr == NULL) {
    e_debug_file_not_found(E_DEBUG_SUBSYSTEM_SDL, atlas_path);
    return 1;
  }
  fclose(file_ptr);

  atlas->surface = SDL_LoadBMP(atlas_path);
  atlas->texture = SDL_CreateTextureFromSurface(sdl_context->renderer, atlas->surface);

  e_debug_init_sequence_success(E_DEBUG_SUBSYSTEM_SDL, 1, 1, "Loaded texture atlas");
  
  return 0;
}

void p_render_free_atlas(e_sdl_texture_atlas_t * atlas) {
  SDL_FreeSurface(atlas->surface);
  SDL_DestroyTexture(atlas->texture);
}

void p_render_atlas_coord(e_sdl_context_t * sdl_context, e_sdl_texture_atlas_t * atlas,
			  p_render_atlas_coord_t source, p_render_atlas_coord_t dest) {
  // if coordinate.index >= 0, convert it to a 2d index and use that instead of coordinate.x and coordinate.y
  if (source.index >= 0) {
    source.x = (source.index % 16) * source.w;
    source.y = (source.index / 16) * source.h;
  }
  
  SDL_Rect sdl_src = {
    source.x,
    source.y,
    source.w,
    source.h
  };

  SDL_Rect sdl_dest = {
    dest.x,
    dest.y,
    dest.w,
    dest.h
  };
  
  SDL_RenderCopy(sdl_context->renderer, atlas->texture, &sdl_src, &sdl_dest);
}

void p_render_world_data(e_sdl_context_t * sdl_context, e_sdl_texture_atlas_t * atlas,
			 p_world_data_t * world_data) {
  int world_bounds = world_data->width * world_data->length * world_data->depth;
  p_render_atlas_coord_t atlas_source = {0, 0, 16, 16, 0};
  // tile width and height stored here
  p_render_atlas_coord_t screen_dest = {0, 0, 32, 32, -1};

  for (int i = 0 ; i < world_bounds ; i++) {
    // get screen coordinates for drawing object
    p_world_pos_t pos = p_world_1d_to_3d(world_data, i);
    screen_dest.x = pos.x * screen_dest.w;
    screen_dest.y = pos.y * screen_dest.h;

    // set texture atlas lookup location
    int id = world_data->objects[i];
    int texture_id = e_object_data_get_object_def(id)->texture_uv;
    atlas_source.index = texture_id;

    // shade based on object z coordinate
    int shade = (pos.z * 15) + 32;
    SDL_SetTextureColorMod(atlas->texture, shade, shade, shade);
    
    // render call
    p_render_atlas_coord(sdl_context, atlas, atlas_source, screen_dest);
  }
}
