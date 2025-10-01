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
        input_state.input_code[i] = 0;
    }
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
            input_state.key_state[event.key.keysym.sym] = true;
            break;
                
        case SDL_KEYUP:
            input_state.key_state[event.key.keysym.sym] = false;
            break;    
            
        default:
            break;
    }
}

e_input_state_t e_input_get_state (void) {
    return input_state;
}

void e_input_print_state (void) {
    printf("KEY STATE: \n");
    int keys_pressed = 0;
    
    // iterate through the input state
    for (int i = 0 ; i < E_SDL_KEYDOWN_EVENTS ; i++) {
        if (input_state.key_state[i] == true) {
            // if a key is pressed, print out its keycode, then increment keys_pressed
            printf("\t%d", i);
            keys_pressed++;
        }
    }
    
    if (keys_pressed > 0){
        printf("\n");
    }
}