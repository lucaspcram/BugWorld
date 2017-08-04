#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <stdbool.h>

bool exit_flag;

struct state {
	/* Lifecycle functions */
	int (*init)(void);
	int (*destroy)(void);
	int (*pause)(void);
	int (*resume)(void);
	
	/* State functions */
	void (*update)(void);
	void (*handle_input)(char);
	void (*render)(void);
};

void init_state_manager();
void destroy_state_manager();
void handle_input(char input);
void update_render();

#endif
