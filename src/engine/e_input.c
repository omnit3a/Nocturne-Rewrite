// standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// external libraries
#include <SDL2/SDL.h>

// internal headers
#include <engine/e_input.h>

e_input_state_t input_state;

void e_input_initialize_state (void) {
    // initialize the current keyboard input state
    input_state.should_quit = false;
    
    for (int i = 0 ; i < E_SDL_KEYDOWN_EVENTS ; i++) {
        input_state.key_state[i] = false;
    }
    
    for (int i = 0 ; i < E_SDL_KEYMOD_EVENTS ; i++) {
        input_state.mod_state[i] = false;
    }
}

void e_input_update_mod_state (void) {
    SDL_Keymod mod_state = SDL_GetModState();
    
    int mod = 0x0000;
    int index = 0;
    do {
        input_state.mod_state[index] = (mod_state & mod) > 0;

        mod = mod << 1;
        index++;
        
        if (!mod){
            mod++;
            continue;
        }
        
    } while (mod <= 0x8000);
    
    // left ctrl | right ctrl
    input_state.mod_state[14] = ((mod_state & 0x0040) | (mod_state & 0x0080)) > 0;

    // left shift | right shift
    input_state.mod_state[15] = ((mod_state & 0x0001) | (mod_state & 0x0002)) > 0;
    
    // left alt | right alt
    input_state.mod_state[16] = ((mod_state & 0x0100) | (mod_state & 0x0200)) > 0;
    
    // left gui | right gui
    input_state.mod_state[17] = ((mod_state & 0x0400) | (mod_state & 0x0800)) > 0;
}

void e_input_handle (void) {
    SDL_Event event;
    
    if (SDL_PollEvent(&event) <= 0) {
        return;
    }
    
    switch (event.type) {
        case SDL_QUIT:
            input_state.should_quit = true;
            break;
            
        case SDL_KEYDOWN:
            e_input_update_mod_state();
            
            if (event.key.keysym.sym >= E_SDL_KEYDOWN_EVENTS){
                break;
            }
            
            input_state.key_state[event.key.keysym.sym] = true;
            break;
                
        case SDL_KEYUP:
            e_input_update_mod_state();
            
            if (event.key.keysym.sym >= E_SDL_KEYDOWN_EVENTS){
                break;
            }
            
            input_state.key_state[event.key.keysym.sym] = false;
            break;    
            
        default:
            break;
    }
}

e_input_state_t e_input_get_state (void) {
    return input_state;
}