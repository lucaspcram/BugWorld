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

	// Perlin generation parameters
	double const freq = 80;
	double const ampl = 100.0;
	double const water_thresh = 35;
	double const grass_thresh = 57;
	int const scale = 255;

	if (m == NULL)
		return;

	init_perlin(true);
	rows = map_rows(m);
	cols = map_cols(m);

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			map_set(m, i, j, E_EMPTY);
			x = (j / (double) cols) * scale;
			y = (i / (double) rows) * scale;
			n = p_noise(x / freq, y / freq) * ampl;
			if (n < water_thresh) {
				map_set(m, i, j, E_WATER);
			} else if (n > grass_thresh) {
				map_set(m, i, j, E_GRASS);
			}
		}
	}
}
