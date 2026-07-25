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
			  p_render_atlas_coord_t coordinate) {
  // if coordinate.index >= 0, convert it to a 2d index and use that instead of coordinate.x and coordinate.y
  if (coordinate.index >= 0) {
    coordinate.x = (coordinate.index % 16) * coordinate.w;
    coordinate.y = (coordinate.index / 16) * coordinate.h;
  }
  
  SDL_Rect source = {
    coordinate.x,
    coordinate.y,
    coordinate.w,
    coordinate.h
  };

  SDL_Rect dest = {
    coordinate.x * 2,
    coordinate.y * 2,
    coordinate.w * 2,
    coordinate.h * 2
  };
  
  SDL_RenderCopy(sdl_context->renderer, atlas->texture, &source, &dest);
}
