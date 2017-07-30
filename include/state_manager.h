#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#define M_CIRCBUF_SIZE 32

struct state {
	/* Lifecycle functions */
	int (*init)(void);
	int (*destroy)(void);
	void (*pause)(void);
	void (*resume)(void);
	
	/* State functions */
	void (*update)(void);
	void (*update_input)(void);
	void (*render)(void);
};

/* 
A LIFO buffer that overwrites oldest elements
when it reaches capacity 
*/
struct state_circbuf {
	struct state ** buf;
	int cur;
};

static struct state_circbuf * states;

void init_state_manager();

void destroy_state_manager();

void push_state(struct state_circbuf * buf, struct state * state);

void pop_state(struct state_circbuf * buf);

struct state * peek_state(struct state_circbuf * buf);

#endif
