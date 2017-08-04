#ifndef MENU_STATE_H
#define MENU_STATE_H

int menu_state_init(void);
int menu_state_destroy(void);
int menu_state_pause(void);
int menu_state_resume(void);
void menu_state_update(void);
void menu_state_update_input(char input);
void menu_state_render(void);

#endif