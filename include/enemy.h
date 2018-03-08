#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"
#include "map.h"

#include <stdint.h>

/*
 * Controls enemy animations and AI.
 */

struct enemy;

struct enemy * create_enemy(int col, int row);
void destroy_enemy(struct enemy * e);

void tick_enemy(struct enemy * e, uint64_t elapsed);
void render_enemy(struct enemy * e);

struct sprite * enemy_get_sprite(struct enemy const * e);
int enemy_get_col(struct enemy const * e);
int enemy_get_row(struct enemy const * e);
void act_enemy(struct enemy * e, struct map const * m, int pl_c, int pl_r);

#endif
