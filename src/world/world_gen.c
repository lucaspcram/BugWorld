#include "world/world_gen.h"

#include "common.h"
#include "world/map.h"

#include <stdlib.h>

void fill_map(struct map * m)
{
	int i;
	int j;
	int r;
	
	if (m == NULL)
		return;
	
	for (i = 0; i < rows(m); i++) {
		for (j = 0; j < cols(m); j++) {
			r = get_rand_int(0, 5);
			switch(r) {
				case 0:
					map_set(m, i, j, E_EMPTY);
					break;
				case 1:
					map_set(m, i, j, E_GRASS);
					break;
				case 2:
					map_set(m, i, j, E_WATER);
					break;
				case 3:
					map_set(m, i, j, E_MOUND);
					break;
				case 4:
					map_set(m, i, j, E_GOAL);
					break;
			}
		}
	}
}
