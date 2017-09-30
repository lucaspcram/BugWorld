#ifndef MAP_H
#define MAP_H

#include <stdint.h>

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
void render_map(struct map * m);

int map_rows(struct map * m);
int map_cols(struct map * m);

void map_set(struct map * m, int i, int j, enum tile_type tile);

#endif
