#include "states/play_state.h"

#include "gameobj/player.h"
#include "gameobj/sprite.h"
#include "view.h"
#include "world/world.h"

#include <stdlib.h>

static struct world * g_world = NULL;

int play_state_init(void)
{
	if (g_world == NULL)
		g_world = create_world();
	return 0;
}

int play_state_destroy(void)
{
	destroy_world(g_world);
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

void play_state_tick(void)
{
	tick_sprite(g_world->player->psprite);
}

void play_state_handle_input(int input)
{
	handle_input_world(g_world, input);
}

void play_state_render(void)
{
	if (g_world == NULL)
		return;

	render_sprite(g_world->player->psprite, M_CYAN);
}
