#ifndef SCORE_STATE_H
#define SCORE_STATE_H

#include <stdint.h>

/*
 * Code for the score state.
 */

int score_state_init(void);
int score_state_destroy(void);
int score_state_pause(void);
int score_state_resume(void);
void score_state_tick(uint64_t elapsed);
void score_state_handle_input(int input);
void score_state_render(void);
void score_state_recv_msg(void * msg);

#endif
