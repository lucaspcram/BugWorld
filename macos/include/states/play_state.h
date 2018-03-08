#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <stdint.h>

/*
 * Code for the play game state.
 */

int play_state_init(void);
int play_state_destroy(void);
int play_state_pause(void);
int play_state_resume(void);
void play_state_tick(uint64_t elapsed);
void play_state_handle_input(int input);
void play_state_render(void);
void play_state_recv_msg(void * msg);

#endif
