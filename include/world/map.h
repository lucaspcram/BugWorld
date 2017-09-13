#ifndef MAP_H
#define MAP_H

enum tile_type {
	EMPTY,
	GRASS,
	WATER,
	MOUND,
	GOAL
};

struct map;

struct map * create_map(int row, int col);
void destroy_map(struct map * m);

void tick_map(struct map * m);
void render_map(struct map * m);

int rows(struct map * m);
int cols(struct map * m);

void map_set(struct map * m, int i, int j, enum tile_type tile);

#endif
