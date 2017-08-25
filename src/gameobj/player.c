#include "gameobj/player.h"

#include "gameobj/sprite.h"
#include "util.h"
#include "view.h"

#include <stdlib.h>

/* Anim params */
/***************/
#define M_PLAYER_WIDTH (1)
#define M_PLAYER_HEIGHT (1)
#define M_ANIM_TIMER_RESET (35)

static const char * G_FRAMES[] = {
	"X",
	"x"
};
static const int G_FRAMES_LEN = 2;
/******END SECTION******/

struct player * create_player(int row, int col)
{
	struct player * new_player;
	new_player = (struct player *) malloc(sizeof(*new_player));
	if (new_player == NULL)
		abort_game("malloc failed in function \'create_player\'");

	new_player->psprite = create_sprite(row, col, M_PLAYER_WIDTH, M_PLAYER_HEIGHT);
	set_anim_params(new_player->psprite, 0, 0, M_ANIM_TIMER_RESET);
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

void update_player(struct player * p)
{
	if (p == NULL)
		return;

	update_sprite(p->psprite);
}

void render_player(struct player * p)
{
	if (p == NULL)
		return;

	render_sprite(p->psprite, M_MAGENTA);
}
