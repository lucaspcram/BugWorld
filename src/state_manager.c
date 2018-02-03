#include "state_manager.h"

#include "common.h"
#include "pthread.h"
#include "states/menu_state.h"
#include "states/play_state.h"
#include "states/dead_state.h"
#include "states/goal_state.h"
#include "states/over_state.h"
#include "states/score_state.h"
#include "states/help_state.h"
#include "states/seed_state.h"
#include "states/state_codes.h"
#include "view.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define M_INIT_STATE(ST, st)                                           \
do {                                                                   \
g_state_tab[M_STATE_ ## ST].init = &st ## _state_init;                 \
g_state_tab[M_STATE_ ## ST].destroy = &st ## _state_destroy;           \
g_state_tab[M_STATE_ ## ST].pause = &st ## _state_pause;               \
g_state_tab[M_STATE_ ## ST].resume = &st ## _state_resume;             \
g_state_tab[M_STATE_ ## ST].tick = &st ## _state_tick;                 \
g_state_tab[M_STATE_ ## ST].handle_input = &st ## _state_handle_input; \
g_state_tab[M_STATE_ ## ST].render = &st ## _state_render;             \
g_state_tab[M_STATE_ ## ST].recv_msg = &st ## _state_recv_msg;         \
} while(0)

/* index into the state table */
static int g_cur_state;

/* each possible game state */
static struct state g_state_tab[M_NUM_STATES];

static void set_cur_state(int code);

void init_state_manager(void)
{
    exit_flag = false;

    M_INIT_STATE(MENU, menu);
    M_INIT_STATE(PLAY, play);
    M_INIT_STATE(DEAD, dead);
    M_INIT_STATE(GOAL, goal);
    M_INIT_STATE(OVER, over);
    M_INIT_STATE(SCORE, score);
    M_INIT_STATE(HELP, help);
    M_INIT_STATE(SEED, seed);

    g_cur_state = M_STATE_MENU;
    g_state_tab[g_cur_state].init();
}

void destroy_state_manager(void)
{

}

void handle_input(int input)
{
    g_state_tab[g_cur_state].handle_input(input);
}

void tick_render(uint64_t elapsed)
{
    g_state_tab[g_cur_state].tick(elapsed);

    clear_view();
    g_state_tab[g_cur_state].render();
    refresh_view();
}

static void set_cur_state(int code)
{
    if (code < 0 || code >= M_NUM_STATES)
        return;
    g_cur_state = code;
}

/* Services declared in state_codes.h */
/**************************************/

void change_state(int exit_mode, int start_mode, int code)
{
    if (code < 0 || code >= M_NUM_STATES)
        return;

    switch (exit_mode) {

        case M_EXIT_DESTROY:
        g_state_tab[g_cur_state].destroy();
        break;

        case M_EXIT_PAUSE:
        g_state_tab[g_cur_state].pause();
        break;

        default:
        return;

    }

    switch (start_mode) {

        case M_START_INIT:
        g_state_tab[code].init();
        break;

        case M_START_RESUME:
        g_state_tab[code].resume();
        break;

        default:
        return;

    }

    set_cur_state(code);
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

/*
 * Calls the recv_msg callback associated with the
 * given state code.
 */
void send_msg(int code, void * msg)
{
    g_state_tab[code].recv_msg(msg);
}
/******END SECTION******/
