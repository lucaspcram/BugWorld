#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include <stdint.h>

/*
 * Container object for the game map. Also defines custom tile types.
 */

enum tile_type {
	E_EMPTY,
	E_GRASS,
	E_WATER,
	E_MOUND,
	E_GOAL
};

struct map;

struct map * create_map(int row, int col);
void destroy_map(struct map * m);

void tick_map(struct map * m, uint64_t elapsed);
void render_map(struct map const * m);

int map_rows(struct map const * m);
int map_cols(struct map const * m);

void map_set(struct map * m, int i, int j, enum tile_type tile);

bool map_point_ingrass(struct map const * m, int row, int col);

#endif
