#ifndef GAME_H
#define GAME_H

/*
 * The core game code. Sets up the SIGALRM for dynamic
 * updates, initializes the game, etc.
 */

enum concurrency_backend {
	E_PTHREAD,
	E_SIGALRM
};

extern enum concurrency_backend g_backend;

void init_game(void);
void input_loop(void);
void * tick(void * arg);

#endif
