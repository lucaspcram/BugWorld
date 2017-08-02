#include "state_manager.h"
#include "state_codes.h"

#include <stdlib.h>
#include <string.h>

// index into the state table
static int cur_state;

// each possible game state
static struct state state_tab[NUM_STATES];

static void set_cur_state(int code);

void init_state_manager()
{

}

void destroy_state_manager()
{

}

static void set_cur_state(int code)
{
	// return immediately on bad state code
	if (code < 0 || code >= NUM_STATES)
		return;
	cur_state = code;
}

void init_state(int code)
{
	state_tab[cur_state].pause();
	set_cur_state(code);
	state_tab[code].init();
}

void resume_state(int code)
{
	state_tab[cur_state].pause();
	set_cur_state(code);
	state_tab[code].resume();
}
