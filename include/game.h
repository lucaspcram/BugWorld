#ifndef GAME_H
#define GAME_H

/*
 * The core game code. Sets up the thread backend for dynamic
 * updates, initializes the game, etc.
 */

#define M_DEFAULT_FPS (10)

extern int g_fps;
extern int g_seed;

void init_game(void);
void input_loop(void);
void * tick(void * arg);

#endif
