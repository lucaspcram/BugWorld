#ifndef PLAYER_H
#define PLAYER_H

#include "gameobj/sprite.h"

#include <stdbool.h>
#include <stdint.h>

/*
 * Controls player animations and game actions.
 */

static int const G_PLAYER_MAX_STAM = 10;
static int const G_PLAYER_MAX_DECOY = 3;

struct player;

struct player * create_player(int col, int row);
void destroy_player(struct player * p);

void tick_player(struct player * p, uint64_t elapsed);
void render_player(struct player const * p);

struct sprite * player_get_sprite(struct player const * p);
int player_get_stamina(struct player const * p);
int player_get_decoys(struct player const * p);

void player_deplete_stamina(struct player * p);
bool player_has_stamina(struct player const * p);
void player_reset_stamina(struct player * p);
void player_inc_stamina(struct player * p);

int player_get_col(struct player const * p);
int player_get_row(struct player const * p);
void player_set_pos(struct player * p, int new_col, int new_row);

#endif
