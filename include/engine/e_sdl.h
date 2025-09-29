#ifndef ENGINE_SDL_H_
#define ENGINE_SDL_H_

// standard library
#include <stdint.h>

// external libraries
#include <SDL2/SDL.h>

// engine window object
typedef struct e_sdl_window_s {
    uint32_t x_position;
    uint32_t y_position;
    uint32_t x_size;
    uint32_t y_size;
    SDL_Window * window;
} e_sdl_window_t;

// engine rendering context object
typedef struct e_sdl_context_s {
	e_sdl_window_t * window;
	SDL_Renderer * renderer;
	SDL_Surface * surface;
    SDL_Texture * texture;
} e_sdl_context_t;

int e_sdl_init (uint32_t flags);
e_sdl_window_t e_sdl_create_window (char * window_title, uint32_t x_size, uint32_t y_size);
e_sdl_context_t e_sdl_create_context (e_sdl_window_t * window);
void e_sdl_destroy_context (e_sdl_context_t * context);
e_sdl_context_t e_sdl_setup (char * title, uint32_t x_size, uint32_t y_size, uint32_t flags);
void e_sdl_quit (e_sdl_context_t * context);
void e_sdl_redraw (e_sdl_context_t * context);

#endif