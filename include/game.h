#ifndef GAME_H
#define GAME_H

/*
 * The core game code. Sets up the SIGALRM for dynamic
 * updates, initializes the game, etc.
 */

void init_game(void);
void * input_loop(void * arg);
void tick(void);

#endif
