#include "gameobj/player.h"

#include "common.h"
#include "gameobj/sprite.h"
#include "view.h"

#include <stdint.h>
#include <stdlib.h>

struct player {
	struct sprite * psprite;
	int stamina;
	int decoys;
};

/* Anim params */
/***************/
#define M_PLAYER_WIDTH (1)
#define M_PLAYER_HEIGHT (1)
#define M_ANIM_TIMER (1000)

static const char * G_FRAMES[] = {
	"X",
	"x"
};
static const int G_FRAMES_LEN = 2;
/******END SECTION******/

struct player * create_player(int row, int col)
{
	struct player * new_player;
	new_player = M_SAFEMALLOC(sizeof(*new_player));

	new_player->psprite = create_sprite(row, col, M_PLAYER_WIDTH, M_PLAYER_HEIGHT);
	set_anim_params(new_player->psprite, 0, 0, M_ANIM_TIMER);
	set_frames(new_player->psprite, G_FRAMES, G_FRAMES_LEN);

	return new_player;
}

void destroy_player(struct player * p)
{
	if (p == NULL)
		return;

	destroy_sprite(p->psprite);
	free(p);
}

void tick_player(struct player * p, uint64_t elapsed)
{
	if (p == NULL)
		return;

	tick_sprite(p->psprite, elapsed);
}

void render_player(struct player * p)
{
	if (p == NULL)
		return;

	render_sprite(p->psprite, M_MAGENTA);
}

int player_row(struct player * p)
{
	if (p == NULL)
		return -1;
	
	return sprite_row(p->psprite);
}

int player_col(struct player * p)
{
	if (p == NULL)
		return -1;
	
	return sprite_col(p->psprite);
}

void player_set_row(struct player * p, int row)
{
	if (p == NULL)
		return;
	
	sprite_set_row(p->psprite, row);
}

void player_set_col(struct player * p, int col)
{
	if (p == NULL)
		return;
	
	sprite_set_col(p->psprite, col);
}
