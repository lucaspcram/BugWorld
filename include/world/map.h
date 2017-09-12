#ifndef MAP_H
#define MAP_H

enum tile_type {
	EMPTY,
	BUSH,
	WATER,
	MOUND,
	GOAL
};

struct map {
	int rows;
	int cols;

	enum tile_type ** tiles;
};

struct map * create_map(int row, int col);
void destroy_map(struct map * m);

#endif
