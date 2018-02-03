
#ifndef STATE_CODES_H
#define STATE_CODES_H

/*
 * Contains codes for the game states as well as definitions
 * for functions that states use to hook into the manager.
 */

/* Manually set this to the number of defined states */
#define M_NUM_STATES (8)

/* Define all states below */
#define M_STATE_MENU (0)
#define M_STATE_PLAY (1)
#define M_STATE_DEAD (2)
#define M_STATE_GOAL (3)
#define M_STATE_OVER (4)
#define M_STATE_SCORE (5)
#define M_STATE_HELP (6)
#define M_STATE_SEED (7)

#define M_EXIT_DESTROY (0)
#define M_EXIT_PAUSE (1)
#define M_START_INIT (0)
#define M_START_RESUME (1)

/*
 * Functions that allow game states to
 * request services from the state manager.
 * These are implemented in state_manager.c
 */
void change_state(int exit_mode, int start_mode, int code);
void force_exit(void);
void send_msg(int code, void * msg);

#endif
