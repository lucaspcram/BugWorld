#include "world/world.h"

#include "common.h"
#include "gameobj/player.h"
#include "key_bindings.h"
#include "world/world_gen.h"

#include <stdlib.h>

struct world {
	struct player * player;
};

struct world * create_world(void)
{
	struct world * new_world;

	new_world = M_SAFEMALLOC(sizeof(struct world));
	new_world->player = create_player(2, 2);

	return new_world;
}

void destroy_world(struct world * w)
{
	if (w == NULL)
		return;

	destroy_player(w->player);
	free(w);
}

void handle_input_world(struct world * w, int input)
{
	if (w == NULL)
		return;
}

void tick_world(struct world * w)
{
	if (w == NULL)
		return;

	tick_player(w->player);
}

void render_world(struct world * w)
{
	if (w == NULL)
		return;

	render_player(w->player);
}

struct player * get_player(struct world * w)
{
	if (w == NULL)
		return NULL;

	return w->player;
}
