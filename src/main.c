// standard library
#include <stdio.h>
#include <stdlib.h>

// external libraries
#include <SDL2/SDL.h>

// internal headers
#include <engine/e_sdl.h>

int main (int argc, char ** argv) {
    e_sdl_context_t context = e_sdl_setup("Noc90", 640, 480, SDL_INIT_VIDEO);
    
    // main event loop
    int running = 1;
    while (running) {
        SDL_Event event;
        e_sdl_redraw(&context);
        
        if (SDL_PollEvent(&event) <= 0) {
            continue;
        }
        
        if (event.type == SDL_QUIT) {
            running = 0;
            break;
        }
        
        // insert gameplay loop here
    }
    
    e_sdl_quit(&context);
    return 0;
}