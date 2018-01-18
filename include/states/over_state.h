#ifndef OVER_STATE_H
#define OVER_STATE_H

#include <stdint.h>

/*
 * Code for the game over state.
 */

int over_state_init(void);
int over_state_destroy(void);
int over_state_pause(void);
int over_state_resume(void);
void over_state_tick(uint64_t elapsed);
void over_state_handle_input(int input);
void over_state_render(void);

#endif
