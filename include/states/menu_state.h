#ifndef MENU_STATE_H
#define MENU_STATE_H

/*
 * Code for the main menu game state.
 */

int menu_state_init(void);
int menu_state_destroy(void);
int menu_state_pause(void);
int menu_state_resume(void);
void menu_state_tick(void);
void menu_state_handle_input(int input);
void menu_state_render(void);

#endif
