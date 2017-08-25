#include "states/play_state.h"

#include "gameobj/player.h"
#include "key_bindings.h"

static struct player * pl;

int play_state_init(void)
{
	pl = create_player(3, 3);

	return 0;
}

int play_state_destroy(void)
{
	destroy_player(pl);

	return 0;
}

int play_state_pause(void)
{
	return 0;
}

int play_state_resume(void)
{
	return 0;
}

void play_state_update(void)
{
	update_player(pl);
}

void play_state_handle_input(int input)
{
	if (input == M_ACTION_UP) {
		pl->psprite->row = pl->psprite->row - 1;
	}
	if (input == M_ACTION_DOWN) {
		pl->psprite->row = pl->psprite->row + 1;
	}
	if (input == M_ACTION_LEFT) {
		pl->psprite->col = pl->psprite->col - 1;
	}
	if (input == M_ACTION_RIGHT) {
		pl->psprite->col = pl->psprite->col + 1;
	}
}

void play_state_render(void)
{
	render_player(pl);
}
