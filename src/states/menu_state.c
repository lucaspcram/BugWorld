#include "states/menu_state.h"
#include "states/state_codes.h"
#include "view.h"
#include "key_bindings.h"
#include "util.h"
#include "sprite.h"

#include <string.h>

/* Menu component defines */
/**************************/

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

#define M_NUM_OPTIONS (3)
#define M_OPTION_PLAY (0)
#define M_OPTION_SCORES (1)
#define M_OPTION_HELP (2)

// Play selection
static char const * MENU_PLAY[] =
{
"+-+-+-+-+-+-+", // animated border frame 1
"| |P|L|A|Y| |",
"x-x-x-x-x-x-x" // animated border frame 2
};
static int MENU_PLAY_ROW_OFFSET;

// Scores selection
static char const * MENU_SCORES[] =
{
"+-+-+-+-+-+-+", // animated border frame 1
"|S|C|O|R|E|S|",
"x-x-x-x-x-x-x" // animated border frame 2
};
static int MENU_SCORES_ROW_OFFSET;

// Help selection
static char const * MENU_HELP[] =
{
"+-+-+-+-+-+-+", // animated border frame 1
"| |H|E|L|P| |",
"x-x-x-x-x-x-x" // animated border frame 2
};
static int MENU_HELP_ROW_OFFSET;

// Only need one since each menu option has equal width
static int MENU_COL_OFFSET;

/******END SECTION******/

// menu state vars
static int menu_index;
static int menu_anim_timer;
static int menu_anim_state;
static int title_anim_state;

// TODO testing sprite, remove later
static struct sprite * test_sprite;
static char const * test_sprite_frames[] = 
{
"abacdcefe",
"babdcdfef",
"abacdcefe"
};

static const int test_sprite_len = 3;

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
	MENU_SCORES_ROW_OFFSET = MENU_PLAY_ROW_OFFSET + 3;
	MENU_HELP_ROW_OFFSET = MENU_SCORES_ROW_OFFSET + 3;

	MENU_COL_OFFSET = (M_SCRWIDTH / 2) - ((strlen(MENU_PLAY[0])) / 2);

	test_sprite = create_sprite(2, 15, 3, 3);
	set_frames(test_sprite, test_sprite_frames, test_sprite_len);

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
		menu_anim_state = !menu_anim_state;
		title_anim_state = !title_anim_state;
	}
}

void menu_state_handle_input(int input)
{
	if (input == M_MENU_SELECT) {
		if (menu_index == M_OPTION_PLAY) {
			abort_game("User aborted");
		}
		if (menu_index == M_OPTION_SCORES) {
			abort_game("User aborted");
		}
		if (menu_index == M_OPTION_HELP) {
			abort_game("User aborted");
		}
	}

	if (input == M_MENU_QUIT)
		force_exit();

	if (input == M_MENU_UP) {
		if (menu_index > 0)
			menu_index--;
		menu_anim_state = 0;
	}
	if (input == M_MENU_DOWN) {
		if (menu_index < M_NUM_OPTIONS - 1)
			menu_index++;
		menu_anim_state = 0;
	}
}

void menu_state_render(void)
{
	int i;
	char const * help_hint = "WASD to navigate, ENTER to select, Q to quit";
	int hint_len = strlen(help_hint);

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
			draw_menu_option(MENU_PLAY, MENU_COL_OFFSET, MENU_PLAY_ROW_OFFSET, M_RED, menu_anim_state);
			draw_menu_option(MENU_SCORES, MENU_COL_OFFSET, MENU_SCORES_ROW_OFFSET, M_MAGENTA, 0);
			draw_menu_option(MENU_HELP, MENU_COL_OFFSET, MENU_HELP_ROW_OFFSET, M_MAGENTA, 0);
			break;
		
		case M_OPTION_SCORES:
			draw_menu_option(MENU_PLAY, MENU_COL_OFFSET, MENU_PLAY_ROW_OFFSET, M_MAGENTA, 0);
			draw_menu_option(MENU_SCORES, MENU_COL_OFFSET, MENU_SCORES_ROW_OFFSET, M_RED, menu_anim_state);
			draw_menu_option(MENU_HELP, MENU_COL_OFFSET, MENU_HELP_ROW_OFFSET, M_MAGENTA, 0);
			break;

		case M_OPTION_HELP:
			draw_menu_option(MENU_PLAY, MENU_COL_OFFSET, MENU_PLAY_ROW_OFFSET, M_MAGENTA, 0);
			draw_menu_option(MENU_SCORES, MENU_COL_OFFSET, MENU_SCORES_ROW_OFFSET, M_MAGENTA, 0);
			draw_menu_option(MENU_HELP, MENU_COL_OFFSET, MENU_HELP_ROW_OFFSET, M_RED, menu_anim_state);
			break;
	}

	// render control hints
	draw_str(help_hint, (M_SCRWIDTH / 2) - (hint_len / 2), M_SCRHEIGHT - 1, M_CYAN);

	render_sprite(test_sprite);
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
