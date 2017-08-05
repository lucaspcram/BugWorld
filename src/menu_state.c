#include "menu_state.h"
#include "state_codes.h"
#include "view.h"
#include "key_bindings.h"

#include <string.h>

#define M_NUM_OPTIONS (2)
#define M_OPTION_PLAY (0)
#define M_OPTION_EXIT (1)

/* Title text definitions */
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

/* Play selection */
static char const * MENU_PLAY[] =
{
"+-+-+-+-+", // animated border frame 1
"|P|L|A|Y|",
"x-x-x-x-x" // animated border frame 2
};
static const int MENU_PLAY_ROW_OFFSET = 12;
static int MENU_PLAY_COL_OFFSET;

/* Exit seleciton */
static char const * MENU_EXIT[] =
{
"+-+-+-+-+", // animated border frame 1
"|E|X|I|T|",
"x-x-x-x-x" // animated border frame 2
};
static const int MENU_EXIT_ROW_OFFSET = 16;

static int menu_index;
static int anim_timer;
static int anim_state;

int menu_state_init(void)
{
	menu_index = M_OPTION_PLAY;
	anim_timer = 0;
	anim_state = 0;

	// compute COL offsets for menu options
	MENU_PLAY_COL_OFFSET = (M_SCRWIDTH / 2) - ((strlen(MENU_PLAY[0])) / 2);
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
	anim_timer++;
	if (anim_timer == 30) {
		anim_timer = 0;
		anim_state = 1 - anim_state;
	}
}

void menu_state_handle_input(char input)
{
	if (input == M_MENU_SELECT) {
		if (menu_index == M_OPTION_PLAY) {

		}
		if (menu_index == M_OPTION_EXIT) {
			force_exit();
		}
	}
	if (input == M_MENU_UP) {
		menu_index--;
		if (menu_index < 0)
			menu_index = M_NUM_OPTIONS - 1;
	}
	if (input == M_MENU_DOWN) {
		menu_index++;
		if (menu_index >= M_NUM_OPTIONS)
			menu_index = 0;
	}
}

void menu_state_render(void)
{
	int i;

	// render the title text
	for (i = 0; i < TITLE_LEN; i++) {
		draw_str(TITLE_TEXT[i], 0, TITLE_ROW_OFFSET + i, M_MAGENTA);
	}

	switch (menu_index) {
		case M_OPTION_PLAY:
			if (anim_state == 0) {
				draw_str(MENU_PLAY[0], 35, MENU_PLAY_ROW_OFFSET, M_RED);
				draw_str(MENU_PLAY[1], 35, MENU_PLAY_ROW_OFFSET + 1, M_RED);
				draw_str(MENU_PLAY[0], 35, MENU_PLAY_ROW_OFFSET + 2, M_RED);
			} else {
				draw_str(MENU_PLAY[2], 35, MENU_PLAY_ROW_OFFSET, M_RED);
				draw_str(MENU_PLAY[1], 35, MENU_PLAY_ROW_OFFSET + 1, M_RED);
				draw_str(MENU_PLAY[2], 35, MENU_PLAY_ROW_OFFSET + 2, M_RED);
			}
			draw_str(MENU_EXIT[0], 35, MENU_EXIT_ROW_OFFSET, M_MAGENTA);
			draw_str(MENU_EXIT[1], 35, MENU_EXIT_ROW_OFFSET + 1, M_MAGENTA);
			draw_str(MENU_EXIT[0], 35, MENU_EXIT_ROW_OFFSET + 2, M_MAGENTA);
			break;
		
		case M_OPTION_EXIT:
			draw_str(MENU_PLAY[0], 35, MENU_PLAY_ROW_OFFSET, M_MAGENTA);
			draw_str(MENU_PLAY[1], 35, MENU_PLAY_ROW_OFFSET + 1, M_MAGENTA);
			draw_str(MENU_PLAY[0], 35, MENU_PLAY_ROW_OFFSET + 2, M_MAGENTA);
			if (anim_state == 0) {
				draw_str(MENU_EXIT[0], 35, MENU_EXIT_ROW_OFFSET, M_RED);
				draw_str(MENU_EXIT[1], 35, MENU_EXIT_ROW_OFFSET + 1, M_RED);
				draw_str(MENU_EXIT[0], 35, MENU_EXIT_ROW_OFFSET + 2, M_RED);
			} else {
				draw_str(MENU_EXIT[2], 35, MENU_EXIT_ROW_OFFSET, M_RED);
				draw_str(MENU_EXIT[1], 35, MENU_EXIT_ROW_OFFSET + 1, M_RED);
				draw_str(MENU_EXIT[2], 35, MENU_EXIT_ROW_OFFSET + 2, M_RED);
			}
			break;
	}
}
