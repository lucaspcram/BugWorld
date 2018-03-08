#ifndef HELP_STATE_H
#define HELP_STATE_H

#include <stdint.h>

/*
 * Code for the help state.
 */

int help_state_init(void);
int help_state_destroy(void);
int help_state_pause(void);
int help_state_resume(void);
void help_state_tick(uint64_t elapsed);
void help_state_handle_input(int input);
void help_state_render(void);
void help_state_recv_msg(void * msg);

#endif
