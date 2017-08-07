#include "menu_state.h"
#include "state_codes.h"
#include "view.h"
#include "key_bindings.h"
#include "grass.h"
#include "util.h"

#include <string.h>

#define M_NUM_OPTIONS (3)
#define M_OPTION_PLAY (0)
#define M_OPTION_SCORES (1)
#define M_OPTION_HELP (2)

#define M_MENU_GRASS_LEN (5)

/* Menu component defines */
/***********************/

// Title text definitions
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

// Play selection
static char const * MENU_PLAY[] =
{
"+-+-+-+-+-+-+", // animated border frame 1
"| |P|L|A|Y| |",
"x-x-x-x-x-x-x" // animated border frame 2
};
static int MENU_PLAY_ROW_OFFSET;
// TODO does each menu option need its own COL offset?
static int MENU_PLAY_COL_OFFSET;

// Scores selection
static char const * MENU_SCORES[] =
{
"+-+-+-+-+-+-+", // animated border frame 1
"|S|C|O|R|E|S|",
"x-x-x-x-x-x-x" // animated border frame 2
};
static int MENU_SCORES_ROW_OFFSET;
static int MENU_SCORES_COL_OFFSET;

// Help selection
static char const * MENU_HELP[] =
{
"+-+-+-+-+-+-+", // animated border frame 1
"| |H|E|L|P| |",
"x-x-x-x-x-x-x" // animated border frame 2
};
static int MENU_HELP_ROW_OFFSET;
static int MENU_HELP_COL_OFFSET;

static int menu_index;
static int menu_anim_timer;

// valid values are 0, 1
static int menu_anim_state;
static int title_anim_state;

static struct grass * menu_grass[M_MENU_GRASS_LEN];

/******END SECTION******/

static void draw_menu_option(
	char const ** menu,
	int col_offset,
	int row_offset,
	int color,
	int state
);

int menu_state_init(void)
{
	// init state vars
	menu_index = M_OPTION_PLAY;
	menu_anim_timer = 0;
	menu_anim_state = 0;
	title_anim_state = 0;

	// compute offsets for menu options
	MENU_PLAY_ROW_OFFSET = TITLE_LEN - 0;
	MENU_PLAY_COL_OFFSET = (M_SCRWIDTH / 2) - ((strlen(MENU_PLAY[0])) / 2);
	
	MENU_SCORES_ROW_OFFSET = MENU_PLAY_ROW_OFFSET + 3;
	MENU_SCORES_COL_OFFSET = (M_SCRWIDTH / 2) - ((strlen(MENU_SCORES[0])) / 2);

	MENU_HELP_ROW_OFFSET = MENU_SCORES_ROW_OFFSET + 3;
	MENU_HELP_COL_OFFSET = (M_SCRWIDTH / 2) - ((strlen(MENU_HELP[0])) / 2);

	menu_grass[0] = create_grass(0, 0, 10, 5);
	menu_grass[1] = create_grass(0, 20, 10, 5);
	menu_grass[2] = create_grass(20, 10, 10, 5);
	menu_grass[3] = create_grass(4, 4, 10, 10);
	menu_grass[4] = create_grass(0, 0, 5, 1);

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
	int i;

	menu_anim_timer++;
	if (menu_anim_timer == 30) {
		menu_anim_timer = 0;
		menu_anim_state = !menu_anim_state;
		title_anim_state = !title_anim_state;
	}

	for (i = 0; i < M_MENU_GRASS_LEN; i++) {
		update_grass(menu_grass[i]);
	}
}

void menu_state_handle_input(char input)
{
	if (input == M_MENU_SELECT) {
		if (menu_index == M_OPTION_PLAY) {

		}
		if (menu_index == M_OPTION_SCORES) {

		}
		if (menu_index == M_OPTION_HELP) {

		}
	}

	if (input == M_MENU_QUIT)
		force_exit();

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
	char const * help_hint = "WASD to navigate, ENTER to select, ESC to quit";
	int hint_len = strlen(help_hint);

	// render the grass behind the other components
	for (i = 0; i < M_MENU_GRASS_LEN; i++) {
		render_grass(menu_grass[i]);
	}

	// render the title text
	for (i = 0; i < TITLE_LEN; i++) {
		if (title_anim_state == 0)
			draw_str(TITLE_TEXT[i], 0, TITLE_ROW_OFFSET + i, M_CYAN);
		else
			draw_str(TITLE_TEXT_2[i], 0, TITLE_ROW_OFFSET + i, M_CYAN);
	}

	// render the menu
	switch (menu_index) {
		case M_OPTION_PLAY:
			draw_menu_option(MENU_PLAY, MENU_PLAY_COL_OFFSET, MENU_PLAY_ROW_OFFSET, M_RED, menu_anim_state);
			draw_menu_option(MENU_SCORES, MENU_SCORES_COL_OFFSET, MENU_SCORES_ROW_OFFSET, M_MAGENTA, 0);
			draw_menu_option(MENU_HELP, MENU_HELP_COL_OFFSET, MENU_HELP_ROW_OFFSET, M_MAGENTA, 0);
			break;
		
		case M_OPTION_SCORES:
			draw_menu_option(MENU_PLAY, MENU_PLAY_COL_OFFSET, MENU_PLAY_ROW_OFFSET, M_MAGENTA, 0);
			draw_menu_option(MENU_SCORES, MENU_SCORES_COL_OFFSET, MENU_SCORES_ROW_OFFSET, M_RED, menu_anim_state);
			draw_menu_option(MENU_HELP, MENU_HELP_COL_OFFSET, MENU_HELP_ROW_OFFSET, M_MAGENTA, 0);
			break;

		case M_OPTION_HELP:
			draw_menu_option(MENU_PLAY, MENU_PLAY_COL_OFFSET, MENU_PLAY_ROW_OFFSET, M_MAGENTA, 0);
			draw_menu_option(MENU_SCORES, MENU_SCORES_COL_OFFSET, MENU_SCORES_ROW_OFFSET, M_MAGENTA, 0);
			draw_menu_option(MENU_HELP, MENU_HELP_COL_OFFSET, MENU_HELP_ROW_OFFSET, M_RED, menu_anim_state);
			break;
	}

	// render control hints
	draw_str(help_hint, (M_SCRWIDTH / 2) - (hint_len / 2), M_SCRHEIGHT - 1, M_CYAN);
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
