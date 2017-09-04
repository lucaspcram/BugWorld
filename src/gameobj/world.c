#include "gameobj/world.h"

#include "gameobj/player.h"
#include "key_bindings.h"

#include <stdlib.h>

static struct player * player;

struct world * init_world(void)
{
	player = create_player(0, 0);

	// TODO actually allocate the world
	return NULL;
}

void destroy_world(struct world * w)
{
	if (w == NULL)
		return;

	destroy_player(w->player);
	free(w);
}

void update_world(struct world * w)
{

}

void handle_input_world(struct world * w, int input)
{
	if (w == NULL)
		return;
}

void render_world(struct world * w)
{
	if (w == NULL)
		return;
}
