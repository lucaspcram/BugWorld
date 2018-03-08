#ifndef WORLD_GEN_H
#define WORLD_GEN_H

#include "enemy.h"
#include "player.h"
#include "map.h"

/*
 * Routines for generating unique, random maps.
 */

void fill_map(struct map * m);
int spawn_enemies(struct enemy ** enemies, struct map const * m);
void spawn_player(struct player ** p, struct map const * m);
void spawn_goal(struct map * m);
void spawn_mounds(struct map * m);

#endif
