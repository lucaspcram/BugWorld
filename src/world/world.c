#include "world/world.h"

#include "common.h"
#include "gameobj/player.h"
#include "gameobj/sprite.h"
#include "key_bindings.h"
#include "world/map.h"
#include "world/world_gen.h"
#include "view.h"

#include <stdint.h>
#include <stdlib.h>

struct world {
	struct player * player;
	struct map * map;
};

struct world * create_world(void)
{
	struct world * new_world;

	new_world = M_SAFEMALLOC(sizeof(struct world));
	new_world->player = create_player(2, 2);
	new_world->map = create_map(M_SCRHEIGHT - 2, M_SCRWIDTH);

	fill_map(new_world->map);

	return new_world;
}

void destroy_world(struct world * w)
{
	if (w == NULL)
		return;

	destroy_player(w->player);
	destroy_map(w->map);
	free(w);
}

void handle_input_world(struct world * w, int input)
{
	int p_row;
	int p_col;

	if (w == NULL)
		return;

	p_row = player_row(w->player);
	p_col = player_col(w->player);
	
	if (input == M_ACTION_UP) {
		M_SET_PLAYER_POS(w->player, p_row - 1, p_col);
	}
	if (input == M_ACTION_DOWN) {
		M_SET_PLAYER_POS(w->player, p_row + 1, p_col);
	}
	if (input == M_ACTION_LEFT) {
		M_SET_PLAYER_POS(w->player, p_row, p_col - 1);
	}
	if (input == M_ACTION_RIGHT) {
		M_SET_PLAYER_POS(w->player, p_row, p_col + 1);
	}

	// generate a new world
	// TODO remove this, just for testing
	if (input == M_MENU_SELECT) {
		fill_map(w->map);
	}
}

void tick_world(struct world * w, uint64_t elapsed)
{
	if (w == NULL)
		return;

	tick_player(w->player, elapsed);
	tick_map(w->map, elapsed);
}

void render_world(struct world * w)
{
	if (w == NULL)
		return;

	render_map(w->map);
	render_player(w->player);
}

struct player * get_player(struct world * w)
{
	if (w == NULL)
		return NULL;

	return w->player;
}
