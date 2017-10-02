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
	tick_world(g_world, elapsed);
}

void play_state_handle_input(int input)
{
	if (input == M_MENU_QUIT)
		force_exit();

	handle_input_world(g_world, input);
}

void play_state_render(void)
{
	int i;

	struct player const * p = get_player(g_world);
	int const p_decoys = player_get_decoys(p);
	int const p_stamina = player_get_stamina(p);
	int const s_offset = (M_SCRWIDTH / 2)- 6;

	render_world(g_world);

	/* Draw the stamina bar */
	draw_str("STAMINA", 0, M_SCRHEIGHT - 2, M_MAGENTA);
	draw_str("<", s_offset, M_SCRHEIGHT - 2, M_MAGENTA);
	for (i = 0; i < p_stamina; i++) {
		draw_str("=", s_offset + i + 1, M_SCRHEIGHT - 2, M_MAGENTA);
	}
	for (i = p_stamina; i < M_MAX_STAMINA; i++) {
		draw_str(" ", s_offset + i + 1, M_SCRHEIGHT - 2, M_MAGENTA);
	}
	draw_str(">", s_offset + i + 1, M_SCRHEIGHT - 2, M_MAGENTA);

	/* Draw the decoy bar */
	draw_str("DECOYS", 0, M_SCRHEIGHT - 1, M_MAGENTA);
}
