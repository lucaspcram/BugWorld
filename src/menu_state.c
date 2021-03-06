#include "menu_state.h"

#include "common.h"
#include "sprite.h"
#include "key_bindings.h"
#include "state_codes.h"
#include "view.h"

#include <stdint.h>
#include <string.h>

#define M_DRAW_MENU(type, color, anim)                              \
do {                                                                \
draw_menu_option(G_MENU_ ## type,                                   \
                 G_MENU_COL_OFFSET, G_MENU_ ## type ## _ROW_OFFSET, \
                 color, anim);                                      \
} while(0)

/* Menu component defines */
/**************************/

/* Title text definitions */
static char const * G_TITLE_FRAME1[] =
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
static char const * G_TITLE_FRAME2[] =
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
static const int G_TITLE_LEN = 11;
static const int G_TITLE_ROW_OFFSET = 1;

#define M_NUM_OPTIONS (3)
#define M_OPTION_PLAY (0)
#define M_OPTION_SCORES (1)
#define M_OPTION_HELP (2)

#define M_MS_UPDATETIMER (500)

/* Play selection */
static char const * G_MENU_PLAY[] =
{
"+-+-+-+-+-+-+",
"| |P|L|A|Y| |",
"x-x-x-x-x-x-x"
};
static int G_MENU_PLAY_ROW_OFFSET;

/* Scores selection */
static char const * G_MENU_SCORES[] =
{
"+-+-+-+-+-+-+",
"|S|C|O|R|E|S|",
"x-x-x-x-x-x-x"
};
static int G_MENU_SCORES_ROW_OFFSET;

/* Help selection */
static char const * G_MENU_HELP[] =
{
"+-+-+-+-+-+-+",
"| |H|E|L|P| |",
"x-x-x-x-x-x-x"
};
static int G_MENU_HELP_ROW_OFFSET;

/* Only need one since each menu option has equal width */
static int G_MENU_COL_OFFSET;

/******END SECTION******/

static int g_menu_index;
static int g_menu_anim_timer;
static int g_menu_anim_state;
static int g_title_anim_state;

static void draw_menu_option(char const ** menu,
                             int col_offset, int row_offset,
                             int color, int state);

int menu_state_init(void)
{
    g_menu_index = M_OPTION_PLAY;
    g_menu_anim_timer = 0;
    g_menu_anim_state = 0;
    g_title_anim_state = 0;

    /* compute offsets for menu options */
    G_MENU_PLAY_ROW_OFFSET = G_TITLE_LEN - 0;
    G_MENU_SCORES_ROW_OFFSET = G_MENU_PLAY_ROW_OFFSET + 3;
    G_MENU_HELP_ROW_OFFSET = G_MENU_SCORES_ROW_OFFSET + 3;

    G_MENU_COL_OFFSET = (M_SCRWIDTH / 2) - ((strlen(G_MENU_PLAY[0])) / 2);

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

void menu_state_tick(uint64_t elapsed)
{
    g_menu_anim_timer += elapsed;
    if (g_menu_anim_timer >= ms2ns(M_MS_UPDATETIMER)) {
        g_menu_anim_timer = 0;
        g_menu_anim_state = !g_menu_anim_state;
        g_title_anim_state = !g_title_anim_state;
    }
}

void menu_state_handle_input(int input)
{
    if (input == M_MENU_SELECT) {
        if (g_menu_index == M_OPTION_PLAY) {
            change_state(M_EXIT_DESTROY, M_START_INIT, M_STATE_PLAY);
        }
        if (g_menu_index == M_OPTION_SCORES) {
            change_state(M_EXIT_PAUSE, M_START_INIT, M_STATE_SCORE);
        }
        if (g_menu_index == M_OPTION_HELP) {
            change_state(M_EXIT_PAUSE, M_START_INIT, M_STATE_HELP);
        }
    }

    if (input == M_MENU_QUIT)
        force_exit();

    if (input == M_MENU_UP) {
        if (g_menu_index > 0)
            g_menu_index--;
        g_menu_anim_state = 0;
    }
    if (input == M_MENU_DOWN) {
        if (g_menu_index < M_NUM_OPTIONS - 1)
            g_menu_index++;
        g_menu_anim_state = 0;
    }
}

void menu_state_render(void)
{
    int i;
    char const * help_hint = "WASD to navigate, ENTER to select, Q to quit";
    int hint_len = strlen(help_hint);

    for (i = 0; i < G_TITLE_LEN; i++) {
        if (g_title_anim_state == 0)
            draw_str(G_TITLE_FRAME1[i], 0, G_TITLE_ROW_OFFSET + i, M_CYAN);
        else
            draw_str(G_TITLE_FRAME2[i], 0, G_TITLE_ROW_OFFSET + i, M_CYAN);
    }

    switch (g_menu_index) {
        case M_OPTION_PLAY:
            M_DRAW_MENU(PLAY, M_RED, g_menu_anim_state);
            M_DRAW_MENU(SCORES, M_MAGENTA, 0);
            M_DRAW_MENU(HELP, M_MAGENTA, 0);
            break;
        
        case M_OPTION_SCORES:
            M_DRAW_MENU(PLAY, M_MAGENTA, 0);
            M_DRAW_MENU(SCORES, M_RED, g_menu_anim_state);
            M_DRAW_MENU(HELP, M_MAGENTA, 0);
            break;

        case M_OPTION_HELP:
            M_DRAW_MENU(PLAY, M_MAGENTA, 0);
            M_DRAW_MENU(SCORES, M_MAGENTA, 0);
            M_DRAW_MENU(HELP, M_RED, g_menu_anim_state);
            break;
    }

    draw_str(help_hint,
            (M_SCRWIDTH / 2) - (hint_len / 2), M_SCRHEIGHT - 1,
             M_CYAN);
}

static void draw_menu_option(char const ** menu,
                             int col_offset, int row_offset,
                             int color, int state)
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

void menu_state_recv_msg(void * msg)
{
    
}
