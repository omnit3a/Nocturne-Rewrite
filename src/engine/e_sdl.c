// standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// external libraries
#include <SDL2/SDL.h>

// internal headers
#include <engine/e_sdl.h>
#include <engine/e_debug.h>

int e_sdl_init (uint32_t flags) {
    int status = SDL_Init(flags);
    
    // check for proper initialization of SDL2
    if (status < 0) {
        e_debug_init_sequence_failure(E_DEBUG_SUBSYSTEM_SDL, 1, 1, "SDL2");
        exit(1);
    }
    
    e_debug_init_sequence_success(E_DEBUG_SUBSYSTEM_SDL, 1, 1, "SDL2");
    return status;
}

e_sdl_window_t e_sdl_create_window (char * title, uint32_t x_size, uint32_t y_size) {
    const uint32_t flags = 0;
    e_sdl_window_t window;
    
    window.window = SDL_CreateWindow(title, 0, 0, x_size, y_size, flags);
    
    // check for proper window initialization
    if (window.window == NULL) {
        e_debug_init_sequence_failure(E_DEBUG_SUBSYSTEM_SDL, 1, 1, "Window");
        SDL_Quit();
        exit(1);
    }
    
    // if successful, initialize the engine window object...
    window.x_position = 0;
    window.y_position = 0;
    window.x_size = x_size;
    window.y_size = y_size;
    
    // ...then notify user of successful initialization, then return engine window object
    e_debug_init_sequence_success(E_DEBUG_SUBSYSTEM_SDL, 1, 1, "Window");
    
    return window;
}

e_sdl_context_t  e_sdl_create_context (e_sdl_window_t * window) {
	const uint32_t flags = SDL_RENDERER_PRESENTVSYNC;
    const int context_init_steps = 3;
    int context_init_stage = 1;
	e_sdl_context_t context = {0};

    // copy the engine window object to the engine rendering context object
	memcpy(&context.window, &window, sizeof(e_sdl_window_t *));
	
	context.renderer = SDL_CreateRenderer(context.window->window, -1, flags);
    
    // check for proper renderer initialization
	if (context.renderer == NULL){
	    e_debug_init_sequence_failure(E_DEBUG_SUBSYSTEM_SDL, context_init_stage, context_init_steps, "Renderer");
        
        // free the properly initialized engine rendering context object parameters, then exit
        SDL_DestroyWindow(context.window->window);
		SDL_Quit();
		exit(1);
	}

    // if successful, set the default rendering information...
	SDL_SetRenderDrawColor(context.renderer, 0, 0, 0, 255);
	SDL_RenderSetLogicalSize(context.renderer, window->x_size, window->y_size);	

    // ...then notify user of successful initialization
    context_init_stage = e_debug_init_sequence_success(E_DEBUG_SUBSYSTEM_SDL, context_init_stage, context_init_steps, "Renderer");
    
	context.surface = SDL_GetWindowSurface(context.window->window);

    // check for proper surface initialization
	if (context.surface == NULL){
		e_debug_init_sequence_failure(E_DEBUG_SUBSYSTEM_SDL, context_init_stage, context_init_steps, "Rendering surface");
        
        // free the properly initialized engine rendering context object parameters, then exit
        SDL_DestroyRenderer(context.renderer);
        SDL_DestroyWindow(context.window->window);
		SDL_Quit();
		exit(1);
	}
    
    context_init_stage = e_debug_init_sequence_success(E_DEBUG_SUBSYSTEM_SDL, context_init_stage, context_init_steps, "Rendering surface");

	context.texture = SDL_CreateTextureFromSurface(context.renderer, context.surface);
    
    // check for proper texture initialization
    if (context.texture == NULL) {
        e_debug_init_sequence_failure(E_DEBUG_SUBSYSTEM_SDL, context_init_stage, context_init_steps, "Rendering texture");
        
        // free the properly initialized engine rendering context object parameters, then exit
        SDL_FreeSurface(context.surface);
        SDL_DestroyRenderer(context.renderer);
        SDL_DestroyWindow(context.window->window);
		SDL_Quit();
		exit(1);
    }
    
    // if successful, notify user of proper initialization, then return engine rendering context object
    context_init_stage = e_debug_init_sequence_success(E_DEBUG_SUBSYSTEM_SDL, context_init_stage, context_init_steps, "Rendering texture");
    
	SDL_UpdateWindowSurface(context.window->window);
    e_debug_init_sequence_success(E_DEBUG_SUBSYSTEM_SDL, context_init_stage, context_init_steps, "Engine rendering context object");
	
	return context;
}

void e_sdl_destroy_context (e_sdl_context_t * context) {
    // free the properly initialized engine rendering context object parameters, then exit SDL2
	SDL_DestroyTexture(context->texture);
	SDL_FreeSurface(context->surface);
	SDL_DestroyRenderer(context->renderer);
	SDL_DestroyWindow(context->window->window);
	SDL_Quit();
}

e_sdl_context_t e_sdl_setup (char * title, uint32_t x_size, uint32_t y_size, uint32_t flags) {
    e_sdl_window_t window;
    e_sdl_context_t context;
    
    e_sdl_init(flags);
    
    window = e_sdl_create_window(title, x_size, y_size);
    context = e_sdl_create_context(&window);
    
    return context;
}

void e_sdl_quit (e_sdl_context_t * context) {
    e_sdl_destroy_context(context);
}

void e_sdl_redraw (e_sdl_context_t * context) {
    SDL_RenderPresent(context->renderer);
    SDL_RenderClear(context->renderer);
}
