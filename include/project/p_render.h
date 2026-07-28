#ifndef P_RENDER_H_
#define P_RENDER_H_

// standard library

// external libraries

// internal headers
#include <engine/e_sdl.h>
#include <project/p_world.h>

typedef struct p_render_atlas_coord_s {
  int x;
  int y;
  int w;
  int h;
  int index;
} p_render_atlas_coord_t;

int p_render_load_atlas(e_sdl_context_t * sdl_context, e_sdl_texture_atlas_t * atlas, char * atlas_path);
void p_render_free_atlas(e_sdl_texture_atlas_t * atlas);
void p_render_atlas_coord(e_sdl_context_t * sdl_context, e_sdl_texture_atlas_t * atlas,
			  p_render_atlas_coord_t source, p_render_atlas_coord_t dest);
void p_render_world_data(e_sdl_context_t * sdl_context, e_sdl_texture_atlas_t * atlas,
			 p_world_data_t * world_data);

#endif
