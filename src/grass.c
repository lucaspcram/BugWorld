#include "grass.h"
#include "util.h"
#include "view.h"

#include <stdlib.h>

static char GRASS_PIX[] = 
{
'\\',
'|',
'/',
'|'
};
const int PIX_LEN = 4;

static void advance_state(struct grass * g);

/* Lifecycle functions */
/***********************/
struct grass * create_grass(int col, int row, int width, int height)
{
	struct grass * new_grass;
	const int DEFAULT_TIMER_RESET = 45;

	new_grass = (struct grass *) malloc(sizeof(*new_grass));
	if (new_grass == NULL)
		abort_game("malloc failed in function \'create_grass\'");

	new_grass->col = col;
	new_grass->row = row;
	new_grass->width = width;
	new_grass->height = height;
	new_grass->anim_state = 0;
	new_grass->anim_timer = 0;
	new_grass->timer_reset = DEFAULT_TIMER_RESET;

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
	if (g->anim_timer >= g->timer_reset) {
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

	for (i = g->col; i < g->col + g->width; i++) {
		for (j = g->row; j < g->row + g->height; j++) {
			draw(GRASS_PIX[g->anim_state], i, j, M_GREEN);
		}
	}
}

void set_anim_params(struct grass * g, int anim_state, int anim_timer, int timer_reset)
{
	g->anim_state = anim_state;
	g->anim_timer = anim_timer;
	g->timer_reset = timer_reset;
}

static void advance_state(struct grass * g)
{
	g->anim_state++;
	if (g->anim_state >= PIX_LEN)
		g->anim_state = 0;
}
