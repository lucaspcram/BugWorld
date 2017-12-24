#ifndef PLAYER_H
#define PLAYER_H

#include "gameobj/sprite.h"

#include <stdbool.h>
#include <stdint.h>

/*
 * Controls player animations and game actions.
 */

#define M_SET_PLAYER_POS(player, col, row)       \
do {                                             \
sprite_set_row(player_get_sprite(player), row);  \
sprite_set_col(player_get_sprite(player), col);  \
} while(0)

#define M_GET_PLAYER_ROW(player)       \
sprite_row(player_get_sprite(player))  \

#define M_GET_PLAYER_COL(player)       \
sprite_col(player_get_sprite(player))  \

#define M_MAX_STAMINA (10)
#define M_MAX_DECOYS (3)

struct player;

struct player * create_player(int col, int row);
void destroy_player(struct player * p);

void tick_player(struct player * p, uint64_t elapsed);
void render_player(struct player * p);

struct sprite * player_get_sprite(struct player * p);
int player_get_stamina(struct player const * p);
int player_get_decoys(struct player const * p);

void player_deplete_stamina(struct player * p);
bool player_has_stamina(struct player * p);
void player_reset_stamina(struct player * p);
void player_inc_stamina(struct player * p);

#endif
