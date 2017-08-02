#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

struct state {
	/* Lifecycle functions */
	int (*init)(void);
	int (*destroy)(void);
	void (*pause)(void);
	void (*resume)(void);
	
	/* State functions */
	void (*update)(void);
	void (*update_input)(char);
	void (*render)(void);
};

void init_state_manager();
void destroy_state_manager();

#endif
