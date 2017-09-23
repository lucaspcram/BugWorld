#include "world/world_gen.h"

#include "common.h"
#include "perlin.h"
#include "world/map.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void fill_map(struct map * m)
{
	int i, j;
	int rows, cols;
	double x, y, n;

	if (m == NULL)
		return;

	init_perlin(true);
	rows = map_rows(m);
	cols = map_cols(m);

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			map_set(m, i, j, E_EMPTY);
			x = (j / (double) cols) * 255;
			y = (i / (double) rows) * 255;
			n = p_noise(x / 64.0, y / 64.0) * 100;
			if (n < 40) {
				map_set(m, i, j, E_WATER);
			} else if (n > 55) {
				map_set(m, i, j, E_GRASS);
			}
		}
	}
}
