#include "state_manager.h"
#include "state_codes.h"
#include "menu_state.h"

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// index into the state table
static int cur_state;

// each possible game state
static struct state state_tab[NUM_STATES];

static void set_cur_state(int code);

void init_state_manager()
{
	exit_flag = false;

	// init menu state
	state_tab[STATE_MENU].init = &menu_state_init;
	state_tab[STATE_MENU].destroy = &menu_state_destroy;
	state_tab[STATE_MENU].pause = &menu_state_pause;
	state_tab[STATE_MENU].resume = &menu_state_resume;
	state_tab[STATE_MENU].update = &menu_state_update;
	state_tab[STATE_MENU].handle_input = &menu_state_handle_input;
	state_tab[STATE_MENU].render = &menu_state_render;

	cur_state = STATE_MENU;
	state_tab[cur_state].init();
}

void destroy_state_manager()
{

}

void handle_input(char input)
{
	state_tab[cur_state].handle_input(input);
}

void update_render()
{
	state_tab[cur_state].update();
	state_tab[cur_state].render();
}

static void set_cur_state(int code)
{
	// return immediately on bad state code
	if (code < 0 || code >= NUM_STATES)
		return;
	cur_state = code;
}

/* Functions declared in state_codes.h */
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

void force_exit()
{
	exit_flag = true;
}
