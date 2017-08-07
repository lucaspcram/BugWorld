#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

/*
 * The state manager suite. Interfaces the main game code
 * with the actual state code.
 */

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
	void (*handle_input)(int);
	void (*render)(void);
};

void init_state_manager();
void destroy_state_manager();
void handle_input(int input);
void update_render();

#endif
