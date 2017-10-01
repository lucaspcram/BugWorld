#ifndef ENEMY_H
#define ENEMY_H

#include "gameobj/sprite.h"

#include <stdint.h>

/*
 * Controls enemy animations and AI.
 */

struct enemy;

struct enemy * create_enemy(int row, int col);
void destroy_enemy(struct enemy * e);

#endif
