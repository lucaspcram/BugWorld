#ifndef PLAYER_H
#define PLAYER_H

#include "gameobj/sprite.h"

/*
 * The player code controlling animations and scoring logic.
 */

struct player {
	struct sprite *psprite;
	int decoys;
};

struct player * create_player(int row, int col);
void destroy_player(struct player * p);

void update_player(struct player * p);
void render_player(struct player * p);

#endif
