#ifndef PLAY_STATE_H
#define PLAY_STATE_H

/*
 * Code for the play game state.
 */

int play_state_init(void);
int play_state_destroy(void);
int play_state_pause(void);
int play_state_resume(void);
void play_state_tick(void);
void play_state_handle_input(int input);
void play_state_render(void);

#endif
