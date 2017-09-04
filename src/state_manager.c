#include "state_manager.h"
#include "states/state_codes.h"
#include "states/menu_state.h"
#include "states/play_state.h"
#include "view.h"

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// index into the state table
static int cur_state;

// each possible game state
static struct state state_tab[NUM_STATES];

static void set_cur_state(int code);

void init_state_manager(void)
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

	// init play state
	state_tab[STATE_PLAY].init = &play_state_init;
	state_tab[STATE_PLAY].destroy = &play_state_destroy;
	state_tab[STATE_PLAY].pause = &play_state_pause;
	state_tab[STATE_PLAY].resume = &play_state_resume;
	state_tab[STATE_PLAY].update = &play_state_update;
	state_tab[STATE_PLAY].handle_input = &play_state_handle_input;
	state_tab[STATE_PLAY].render = &play_state_render;

	cur_state = STATE_MENU;
	state_tab[cur_state].init();
}

void destroy_state_manager(void)
{

}

void handle_input(int input)
{
	state_tab[cur_state].handle_input(input);
}

void update_render(void)
{
	state_tab[cur_state].update();

	// refresh the display and draw the current state
	clear_view();
	state_tab[cur_state].render();
	refresh_view();
}

static void set_cur_state(int code)
{
	// return immediately on bad state code
	if (code < 0 || code >= NUM_STATES)
		return;
	cur_state = code;
}

/* Services declared in state_codes.h */
/**************************************/
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

/*
 * Exit flag picked up by game.c. Exits the game
 * with cleanup, compared to abort_game which
 * immediately aborts.
 */
void force_exit(void)
{
	exit_flag = true;
}
/******END SECTION******/
