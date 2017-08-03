#include "menu_state.h"
#include "state_codes.h"
#include "view.h"

static int x;
static int num;

int menu_state_init(void)
{
	x = 0;
	num = 0;
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
	static int timer = 0;

	if (timer == 60) {
		timer = 0;
		num++;
	}
	timer++;
}

void menu_state_handle_input(char input)
{
	if (input == 'q')
		force_exit();
	if (input == 'a')
		x--;
	if (input == 'd')
		x++;
}

void menu_state_render(void)
{
	clear_view();
	draw('a' + num, x, 10, M_RED);
	refresh_view();
}
