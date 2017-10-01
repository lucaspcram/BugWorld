#ifndef PLAYER_H
#define PLAYER_H

#include "gameobj/sprite.h"

#include <stdint.h>

/*
 * Controls player animations and game actions.
 */

#define M_SET_PLAYER_POS(player, row, col)       \
do {                                             \
sprite_set_row(player_get_sprite(player), row);  \
sprite_set_col(player_get_sprite(player), col);  \
} while(0)

#define M_GET_PLAYER_ROW(player)            \
sprite_row(player_get_sprite(player));  \

#define M_GET_PLAYER_COL(player)            \
sprite_col(player_get_sprite(player));  \


struct player;

struct player * create_player(int row, int col);
void destroy_player(struct player * p);

void tick_player(struct player * p, uint64_t elapsed);
void render_player(struct player * p);

struct sprite * player_get_sprite(struct player * p);

#endif
