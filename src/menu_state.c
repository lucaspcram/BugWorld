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
" /+++++++                                                        /++       /++",
"| ++__  ++                                                      | ++      | ++",
"| ++  \\ ++ /++   /++  /++++++  /++  /++  /++  /++++++   /++++++ | ++  /+++++++",
"| +++++++ | ++  | ++ /++__  ++| ++ | ++ | ++ /++__  ++ /++__  ++| ++ /++__  ++",
"| ++__  ++| ++  | ++| ++  \\ ++| ++ | ++ | ++| ++  \\ ++| ++  \\__/| ++| ++  | ++",
"| ++  \\ ++| ++  | ++| ++  | ++| ++ | ++ | ++| ++  | ++| ++      | ++| ++  | ++",
"| +++++++/|  ++++++/|  +++++++|  +++++/++++/|  ++++++/| ++      | ++|  +++++++",
"|_______/  \\______/  \\____  ++ \\_____/\\___/  \\______/ |__/      |__/ \\_______/",
"                     /++  \\ ++                                                ",
"                    |  ++++++/                                                ",
"                     \\______/                                                 "
};
static char const * TITLE_TEXT_2[] =
{
" /xxxxxxx                                                        /xx       /xx",
"| xx__  xx                                                      | xx      | xx",
"| xx  \\ xx /xx   /xx  /xxxxxx  /xx  /xx  /xx  /xxxxxx   /xxxxxx | xx  /xxxxxxx",
"| xxxxxxx | xx  | xx /xx__  xx| xx | xx | xx /xx__  xx /xx__  xx| xx /xx__  xx",
"| xx__  xx| xx  | xx| xx  \\ xx| xx | xx | xx| xx  \\ xx| xx  \\__/| xx| xx  | xx",
"| xx  \\ xx| xx  | xx| xx  | xx| xx | xx | xx| xx  | xx| xx      | xx| xx  | xx",
"| xxxxxxx/|  xxxxxx/|  xxxxxxx|  xxxxx/xxxx/|  xxxxxx/| xx      | xx|  xxxxxxx",
"|_______/  \\______/  \\____  xx \\_____/\\___/  \\______/ |__/      |__/ \\_______/",
"                     /xx  \\ xx                                                ",
"                    |  xxxxxx/                                                ",
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
static int MENU_PLAY_ROW_OFFSET;
static int MENU_PLAY_COL_OFFSET;

/* Exit selection */
static char const * MENU_EXIT[] =
{
"+-+-+-+-+", // animated border frame 1
"|E|X|I|T|",
"x-x-x-x-x" // animated border frame 2
};
static int MENU_EXIT_ROW_OFFSET;
static int MENU_EXIT_COL_OFFSET;

/* state globals */
static int menu_index;
static int menu_anim_timer;

// valid values are 0, 1
static int menu_anim_state;
static int title_anim_state;

static void draw_menu_option(
	char const ** menu,
	int col_offset,
	int row_offset,
	int color,
	int state
);

int menu_state_init(void)
{
	menu_index = M_OPTION_PLAY;
	menu_anim_timer = 0;
	menu_anim_state = 0;
	title_anim_state = 0;

	/* compute offsets for menu options */
	MENU_PLAY_ROW_OFFSET = TITLE_LEN + 1;
	MENU_PLAY_COL_OFFSET = (M_SCRWIDTH / 2) - ((strlen(MENU_PLAY[0])) / 2);
	
	MENU_EXIT_ROW_OFFSET = MENU_PLAY_ROW_OFFSET + 4;
	MENU_EXIT_COL_OFFSET = (M_SCRWIDTH / 2) - ((strlen(MENU_EXIT[0])) / 2);

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
	menu_anim_timer++;
	if (menu_anim_timer == 30) {
		menu_anim_timer = 0;
		menu_anim_state = 1 - menu_anim_state;
		title_anim_state = 1 - title_anim_state;
	}
}

void menu_state_handle_input(char input)
{
	if (input == M_MENU_SELECT) {
		if (menu_index == M_OPTION_PLAY) {

		}
		if (menu_index == M_OPTION_EXIT)
			force_exit();
	}

	if (input == M_MENU_UP) {
		menu_index--;
		menu_anim_state = 0;
		if (menu_index < 0)
			menu_index = M_NUM_OPTIONS - 1;
	}
	if (input == M_MENU_DOWN) {
		menu_index++;
		menu_anim_state = 0;
		if (menu_index >= M_NUM_OPTIONS)
			menu_index = 0;
	}
}

void menu_state_render(void)
{
	int i;

	// render the title text
	for (i = 0; i < TITLE_LEN; i++) {
		if (title_anim_state == 0)
			draw_str(TITLE_TEXT[i], 0, TITLE_ROW_OFFSET + i, M_MAGENTA);
		else
			draw_str(TITLE_TEXT_2[i], 0, TITLE_ROW_OFFSET + i, M_MAGENTA);
	}

	switch (menu_index) {
		case M_OPTION_PLAY:
			draw_menu_option(MENU_PLAY, MENU_PLAY_COL_OFFSET, MENU_PLAY_ROW_OFFSET, M_RED, menu_anim_state);
			draw_menu_option(MENU_EXIT, MENU_EXIT_COL_OFFSET, MENU_EXIT_ROW_OFFSET, M_MAGENTA, 0);
			break;
		
		case M_OPTION_EXIT:
			draw_menu_option(MENU_PLAY, MENU_PLAY_COL_OFFSET, MENU_PLAY_ROW_OFFSET, M_MAGENTA, 0);
			draw_menu_option(MENU_EXIT, MENU_EXIT_COL_OFFSET, MENU_EXIT_ROW_OFFSET, M_RED, menu_anim_state);
			break;
	}
}

static void draw_menu_option(
	char const ** menu,
	int col_offset,
	int row_offset,
	int color,
	int state
)
{
	if (state == 0) {
		draw_str(menu[0], col_offset, row_offset, color);
		draw_str(menu[1], col_offset, row_offset + 1, color);
		draw_str(menu[0], col_offset, row_offset + 2, color);
	} else {
		draw_str(menu[2], col_offset, row_offset, color);
		draw_str(menu[1], col_offset, row_offset + 1, color);
		draw_str(menu[2], col_offset, row_offset + 2, color);
	}
}
