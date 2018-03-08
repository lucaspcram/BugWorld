#ifndef DEAD_STATE_H
#define DEAD_STATE_H

#include <stdint.h>

/*
 * Code for the dead game state.
 */

int dead_state_init(void);
int dead_state_destroy(void);
int dead_state_pause(void);
int dead_state_resume(void);
void dead_state_tick(uint64_t elapsed);
void dead_state_handle_input(int input);
void dead_state_render(void);
void dead_state_recv_msg(void * msg);

#endif
