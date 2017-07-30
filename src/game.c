#include "game.h"
#include "view.h"
#include "state_manager.h"

void init_game(void)
{
	init_graphics();
	init_state_manager();



	destroy_state_manager();
	destroy_graphics();
}