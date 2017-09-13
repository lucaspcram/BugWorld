#ifndef PLAYER_H
#define PLAYER_H

#include "gameobj/sprite.h"

/*
 * The player code controlling animations and scoring logic.
 */

struct player;

struct player * create_player(int row, int col);
void destroy_player(struct player * p);

void tick_player(struct player * p);
void render_player(struct player * p);

#endif
