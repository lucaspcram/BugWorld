#ifndef GAME_H
#define GAME_H

/*
 * The core game code. Sets up the SIGALRM for dynamic
 * updates, initializes the game, etc.
 */

#define M_DEFAULT_FPS (60)

enum concurrency_backend {
	E_PTHREAD,
	E_SIGALRM
};

extern enum concurrency_backend g_backend;
extern int g_fps;

void init_game(void);
void input_loop_pthread(void);
void input_loop_sigalrm(void);
void * tick_pthread(void * arg);
void tick_sigalrm(int sig);
void set_sigalrm(void);

#endif
