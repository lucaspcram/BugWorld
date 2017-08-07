#include "grass.h"
#include "util.h"
#include "view.h"

#include <stdlib.h>

static char GRASS_PIX[] = 
{
'\\',
'|',
'/'
};
const int PIX_LEN = 3;

static void advance_state(struct grass * g);

/* Lifecycle functions */
/***********************/
struct grass * create_grass(int col, int row, int width, int height)
{
	struct grass * new_grass;

	new_grass = (struct grass *) malloc(sizeof(*new_grass));
	if (new_grass == NULL)
		abort_game("malloc failed in function \'create_grass\'");

	new_grass->col = col;
	new_grass->row = row;
	new_grass->width = width;
	new_grass->height = height;
	new_grass->anim_state = 0;
	new_grass->anim_timer = 0;

	return new_grass;
}

void destroy_grass(struct grass * g)
{
	free(g);
}
/******END SECTION******/

void update_grass(struct grass * g)
{
	g->anim_timer++;
	if (g->anim_timer == 30) {
		g->anim_timer = 0;
		advance_state(g);
	}
}

void render_grass(struct grass * g)
{
	int i;
	int j;

	if (g == NULL)
		return;

	for (i = g->col; i < g->width; i++) {
		for (j = g->row; j < g->height; j++) {
			draw(GRASS_PIX[g->anim_state], g->col, g->row, M_GREEN);
		}
	}
}

static void advance_state(struct grass * g)
{
	g->anim_state++;
	if (g->anim_state >= PIX_LEN)
		g->anim_state = 0;
}
