#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <stdint.h>

/*
 * Code for the main menu game state.
 */

int menu_state_init(void);
int menu_state_destroy(void);
int menu_state_pause(void);
int menu_state_resume(void);
void menu_state_tick(uint64_t elapsed);
void menu_state_handle_input(int input);
void menu_state_render(void);
void menu_state_recv_msg(void * msg);

#endif
