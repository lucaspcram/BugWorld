#include "world/map.h"

#include <stdlib.h>

struct map {
	int rows;
	int cols;

	enum tile_type ** tiles;
};

struct map * create_map(int row, int col)
{
	return NULL;
}

void destroy_map(struct map * m)
{
	if (m == NULL)
		return;
}
