#ifndef ENEMY_H
#define ENEMY_H

#include "gameobj/sprite.h"
#include "world/map.h"

#include <stdint.h>

/*
 * Controls enemy animations and AI.
 */

struct enemy;

struct enemy * create_enemy(int col, int row);
void destroy_enemy(struct enemy * e);

void tick_enemy(struct enemy * e, uint64_t elapsed);
void render_enemy(struct enemy * e);

void act_enemy(struct enemy * e, struct map const * m, int pl_c, int pl_r);

#endif
