#include "menu_state.h"
#include "state_codes.h"

int menu_state_init(void)
{
	return 0;
}

int menu_state_destroy(void)
{
	return 0;
}

int menu_state_pause(void)
{
	return 0;
}

int menu_state_resume(void)
{
	return 0;
}

void menu_state_update(void)
{

}

void menu_state_update_input(char input)
{
	if (input == 'q')
		force_exit();
}

void menu_state_render(void)
{

}
