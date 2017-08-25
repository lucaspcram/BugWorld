#ifndef GAME_H
#define GAME_H

/*
 * The core game code. Sets up the SIGALRM for dynamic
 * updates, initializes the game, etc.
 */

#define M_FPS (60)

void init_game(void);
void input_loop(void);
void tick(int sig);
void set_sigalarm();

#endif
