#include "menu_state.h"
#include "state_codes.h"
#include "view.h"
#include "key_bindings.h"
#include <ncurses.h>

static char const * TITLE_TEXT[] =
{
" /#######                                                        /##       /##",
"| ##__  ##                                                      | ##      | ##",
"| ##  \\ ## /##   /##  /######  /##  /##  /##  /######   /###### | ##  /#######",
"| ####### | ##  | ## /##__  ##| ## | ## | ## /##__  ## /##__  ##| ## /##__  ##",
"| ##__  ##| ##  | ##| ##  \\ ##| ## | ## | ##| ##  \\ ##| ##  \\__/| ##| ##  | ##",
"| ##  \\ ##| ##  | ##| ##  | ##| ## | ## | ##| ##  | ##| ##      | ##| ##  | ##",
"| #######/|  ######/|  #######|  #####/####/|  ######/| ##      | ##|  #######",
"|_______/  \\______/  \\____  ## \\_____/\\___/  \\______/ |__/      |__/ \\_______/",
"                     /##  \\ ##                                                ",
"                    |  ######/                                                ",
"                     \\______/                                                 "
};
static const int TITLE_LEN = 11;
static const int TITLE_ROW_OFFSET = 1;

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
	return menu_state_destroy();
}

int menu_state_resume(void)
{
	return menu_state_init();
}

void menu_state_update(void)
{

}

void menu_state_handle_input(char input)
{
	if (input == M_MENU_SELECT)
		force_exit();
}

void menu_state_render(void)
{
	int i;

	// sets background color
	wbkgd(stdscr, COLOR_PAIR(M_MAGENTA));

	// render the title text
	for (i = 0; i < TITLE_LEN; i++) {
		draw_str(TITLE_TEXT[i], 0, TITLE_ROW_OFFSET + i, M_GREEN);
	}
}
