#include "state_manager.h"
#include "states/state_codes.h"
#include "states/menu_state.h"
#include "states/play_state.h"
#include "view.h"

#include <stdlib.h>
#include <string.h>

#define M_INIT_STATE(ST, st)                                       \
do {                                                               \
state_tab[M_STATE_ ## ST].init = &st ## _state_init;                 \
state_tab[M_STATE_ ## ST].destroy = &st ## _state_destroy;           \
state_tab[M_STATE_ ## ST].pause = &st ## _state_pause;               \
state_tab[M_STATE_ ## ST].resume = &st ## _state_resume;             \
state_tab[M_STATE_ ## ST].update = &st ## _state_update;             \
state_tab[M_STATE_ ## ST].handle_input = &st ## _state_handle_input; \
state_tab[M_STATE_ ## ST].render = &st ## _state_render;             \
} while(0)

// index into the state table
static int cur_state;

// each possible game state
static struct state state_tab[M_NUM_STATES];

static void set_cur_state(int code);

void init_state_manager(void)
{
	exit_flag = false;

	// init menu state
	M_INIT_STATE(MENU, menu);
	M_INIT_STATE(PLAY, play);

	cur_state = M_STATE_MENU;
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
	if (code < 0 || code >= M_NUM_STATES)
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
