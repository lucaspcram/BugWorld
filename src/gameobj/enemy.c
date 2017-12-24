#include "gameobj/enemy.h"

#include "common.h"
#include "gameobj/sprite.h"
#include "world/map.h"
#include "view.h"

#include <stdint.h>
#include <stdlib.h>

struct enemy {
	struct sprite * esprite;
};

static const char * G_FRAMES[] = {
	"v",
	"V"
};
static const int G_FRAMES_LEN = 2;
/******END SECTION******/

/* Anim params */
/***************/
#define M_ENEMY_WIDTH (1)
#define M_ENEMY_HEIGHT (1)
#define M_ANIM_TIMER (1000)

struct enemy * create_enemy(int col, int row)
{
	struct enemy * new_enemy;
	new_enemy = M_SAFEMALLOC(sizeof(*new_enemy));

	new_enemy->esprite = create_sprite(col, row, M_ENEMY_WIDTH, M_ENEMY_HEIGHT);
	set_anim_params(new_enemy->esprite, 0, 0, M_ANIM_TIMER);
	set_frames(new_enemy->esprite, G_FRAMES, G_FRAMES_LEN);

	return new_enemy;
}

void destroy_enemy(struct enemy * e)
{
	if (e == NULL)
		return;

	destroy_sprite(e->esprite);
	free(e);
}

void tick_enemy(struct enemy * e, uint64_t elapsed)
{
	if (e == NULL)
		return;

	tick_sprite(e->esprite, elapsed);
}

void render_enemy(struct enemy * e)
{
	if (e == NULL)
		return;

	render_sprite(e->esprite, M_RED);
}

void act_enemy(struct enemy * e, struct map const * m, int pl_c, int pl_r)
{
	int enem_c;
	int enem_r;

	if (map_point_hastype(m, pl_c, pl_r, E_GRASS))
		return;

	enem_c = sprite_col(e->esprite);
	enem_r = sprite_row(e->esprite);
}
