#include "world/world_gen.h"

#include "common.h"
#include "gameobj/player.h"
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

	/* Perlin generation parameters */
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

int spawn_enemies(struct enemy ** enemies, struct map const * m)
{
	int num_enemies;
	int enem_r;
	int enem_c;
	int map_r;
	int map_c;
	int i;

	num_enemies = get_rand_int(6, 10);
	map_r = map_rows(m);
	map_c = map_cols(m);

	i = 0;
	while (i < num_enemies) {
		enem_r = get_rand_int(0, map_r - 1);
		enem_c = get_rand_int(0, map_c - 1);
		if (!map_point_hastype(m, enem_c, enem_r, E_WATER)) {
			enemies[i] = create_enemy(enem_c, enem_r);
			i++;
		} else {
			continue;
		}
	}

	return num_enemies;
}

void spawn_player(struct player ** p, struct map const * m)
{
	int pl_r;
	int pl_c;
	int map_r;
	int map_c;

	map_r = map_rows(m);
	map_c = map_cols(m);

	do {
		pl_r = get_rand_int(0, map_r - 1);
		pl_c = get_rand_int(0, map_c - 1);
	} while(!map_point_hastype(m, pl_c, pl_r, E_GRASS));

	*p = create_player(pl_c, pl_r);
}
