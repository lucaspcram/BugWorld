#ifndef WORLD_GEN_H
#define WORLD_GEN_H

#include "gameobj/enemy.h"
#include "world/map.h"

/*
 * Routines for generating unique, random maps.
 */

void fill_map(struct map * m);
int spawn_enemies(struct enemy ** enemies, struct map * m);

#endif
