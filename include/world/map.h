#ifndef MAP_H
#define MAP_H

enum tile_type {
	EMPTY,
	BUSH,
	WATER,
	MOUND,
	GOAL
};

struct map;

struct map * create_map(int row, int col);
void destroy_map(struct map * m);

void tick_map(struct map * m);
void render_map(struct map * m);

#endif
