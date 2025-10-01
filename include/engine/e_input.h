#ifndef ENGINE_INPUT_H_
#define ENGINE_INPUT_H_

// standard library
#include <stdint.h>
#include <stdbool.h>

#define E_SDL_KEYDOWN_EVENTS 322

typedef struct e_input_state_s {
    bool should_quit;
    bool key_state[E_SDL_KEYDOWN_EVENTS];
    uint16_t input_code[E_SDL_KEYDOWN_EVENTS];
} e_input_state_t;

void e_input_initialize_state (void);
void e_input_handle (void);
e_input_state_t e_input_get_state (void);
void e_input_print_state (void);

#endif