#ifndef WORLD_H
#define WORLD_H

#include "gameobj/player.h"

#include <stdint.h>

/*
 * Container object for the in-game world. The world manages
 * the memory lifetimes of a player, enemies, and obstacles.
 * The world also manages generating new levels and updating
 * game objects.
 */

struct world;

struct world * create_world(void);
void destroy_world(struct world * w);

void handle_input_world(struct world * w, int input);
void tick_world(struct world * w, uint64_t elapsed);
void render_world(struct world const * w);

struct player * get_player(struct world const * w);

bool world_is_complete(struct world const * w);
int world_getscore(struct world const * w);

#endif
