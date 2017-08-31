#include "states/play_state.h"

#include "gameobj/player.h"
#include "gameobj/world.h"

static struct world * world;

int play_state_init(void)
{
	world = init_world();

	return 0;
}

int play_state_destroy(void)
{
	destroy_world(world);
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

}

void play_state_handle_input(int input)
{

}

void play_state_render(void)
{

}
