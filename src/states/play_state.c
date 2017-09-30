#include "states/play_state.h"

#include "gameobj/player.h"
#include "gameobj/sprite.h"
#include "key_bindings.h"
#include "states/state_codes.h"
#include "view.h"
#include "world/world.h"

#include <stdint.h>
#include <stdlib.h>

static struct world * g_world = NULL;

/* TODO debugging remove */
static uint64_t g_test = 0;

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

void play_state_tick(uint64_t elapsed)
{
	//g_test++;
	//if (elapsed > 900000000)
		g_test = elapsed;
	tick_world(g_world, 1);
}

void play_state_handle_input(int input)
{
	if (input == M_MENU_QUIT)
		force_exit();

	handle_input_world(g_world, input);
}

void play_state_render(void)
{
	/* TODO remove debug code below */
	char buf[32];
	sprintf(buf, "%lu", g_test);
	draw_str(buf, 30, M_SCRHEIGHT - 1, M_WHITE);


	render_world(g_world);
	draw_str("UI Line 1", 0, M_SCRHEIGHT - 2, M_WHITE);
	draw_str("UI Line 2", 0, M_SCRHEIGHT - 1, M_WHITE);
}
