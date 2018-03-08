#ifndef GOAL_STATE_H
#define GOAL_STATE_H

#include <stdint.h>

/*
 * Code for the goal completed game state.
 */

int goal_state_init(void);
int goal_state_destroy(void);
int goal_state_pause(void);
int goal_state_resume(void);
void goal_state_tick(uint64_t elapsed);
void goal_state_handle_input(int input);
void goal_state_render(void);
void goal_state_recv_msg(void * msg);

#endif
