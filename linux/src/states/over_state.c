#include "states/over_state.h"

#include "common.h"
#include "key_bindings.h"
#include "scores.h"
#include "states/state_codes.h"
#include "view.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static char const * G_FRAME1_1[] =
{
"  /######   /######  /##      /## /########",
" /##__  ## /##__  ##| ###    /###| ##_____/",
"| ##  \\__/| ##  \\ ##| ####  /####| ##      ",
"| ## /####| ########| ## ##/## ##| #####   ",
"| ##|_  ##| ##__  ##| ##  ###| ##| ##__/   ",
"| ##  \\ ##| ##  | ##| ##\\  # | ##| ##      ",
"|  ######/| ##  | ##| ## \\/  | ##| ########",
" \\______/ |__/  |__/|__/     |__/|________/"
};
static char const * G_FRAME1_2[] =
{
"  /******   /******  /**      /** /********",
" /**__  ** /**__  **| ***    /***| **_____/",
"| **  \\__/| **  \\ **| ****  /****| **      ",
"| ** /****| ********| ** **/** **| *****   ",
"| **|_  **| **__  **| **  ***| **| **__/   ",
"| **  \\ **| **  | **| **\\  * | **| **      ",
"|  ******/| **  | **| ** \\/  | **| ********",
" \\______/ |__/  |__/|__/     |__/|________/"
};

static char const * G_FRAME2_1[] =
{
"  /######  /##    /## /######## /####### ",
" /##__  ##| ##   | ##| ##_____/| ##__  ##",
"| ##  \\ ##| ##   | ##| ##      | ##  \\ ##",
"| ##  | ##|  ## / ##/| #####   | #######/",
"| ##  | ## \\  ## ##/ | ##__/   | ##__  ##",
"| ##  | ##  \\  ###/  | ##      | ##  \\ ##",
"|  ######/   \\  #/   | ########| ##  | ##",
" \\______/     \\_/    |________/|__/  |__/"
};
static char const * G_FRAME2_2[] =
{
"  /******  /**    /** /******** /******* ",
" /**__  **| **   | **| **_____/| **__  **",
"| **  \\ **| **   | **| **      | **  \\ **",
"| **  | **|  ** / **/| *****   | *******/",
"| **  | ** \\  ** **/ | **__/   | **__  **",
"| **  | **  \\  ***/  | **      | **  \\ **",
"|  ******/   \\  */   | ********| **  | **",
" \\______/     \\_/    |________/|__/  |__/"
};

static int const G_FRAME_LEN = 8;
static int const G_TITLE1_ROW_OFFSET = 1;
static int const G_TITLE2_ROW_OFFSET = 10;


static int const G_MS_UPDATETIMER = 500;

static int g_anim_timer;
static int g_anim_state;

static struct score * g_score = NULL;

static void save_score(void);

int over_state_init(void)
{
    return 0;
}

int over_state_destroy(void)
{
    return 0;
}

int over_state_pause(void)
{
    return 0;
}

int over_state_resume(void)
{
    return 0;
}

void over_state_tick(uint64_t elapsed)
{
    g_anim_timer += elapsed;
    if (g_anim_timer >= ms2ns(G_MS_UPDATETIMER)) {
        g_anim_timer = 0;
        g_anim_state = !g_anim_state;
    }
}

void over_state_handle_input(int input)
{
    if (input == M_MENU_SELECT) {
        save_score();
        force_exit();
    }

    if (input == M_MENU_QUIT)
        force_exit();
}

void over_state_render(void)
{
    int i;
    char const * help_hint1 = "ENTER to save score and quit";
    int hint_len1 = strlen(help_hint1);
    char const * help_hint2 = "Q to quit without saving";
    int hint_len2 = strlen(help_hint2);

    for (i = 0; i < G_FRAME_LEN; i++) {
        if (g_anim_state == 0)
            draw_str(G_FRAME1_1[i], 20, G_TITLE1_ROW_OFFSET + i, M_CYAN);
        else
            draw_str(G_FRAME1_2[i], 20, G_TITLE1_ROW_OFFSET + i, M_CYAN);
    }

    for (i = 0; i < G_FRAME_LEN; i++) {
        if (g_anim_state == 0)
            draw_str(G_FRAME2_1[i], 20, G_TITLE2_ROW_OFFSET + i, M_CYAN);
        else
            draw_str(G_FRAME2_2[i], 20, G_TITLE2_ROW_OFFSET + i, M_CYAN);
    }

    draw_str(help_hint1,
            (M_SCRWIDTH / 2) - (hint_len1 / 2), M_SCRHEIGHT - 2,
             M_CYAN);

    draw_str(help_hint2,
            (M_SCRWIDTH / 2) - (hint_len2 / 2), M_SCRHEIGHT - 1,
             M_CYAN);
}

void over_state_recv_msg(void * msg)
{
    g_score = (struct score *) msg;
}

static void save_score(void)
{
    char * path;
    struct score ** scores;

    path = create_scorefile();
    scores = read_scorefile(path);
    scores = add_score(scores, g_score);
    write_scorefile(scores, path);
    free_scorelist(scores);
    free(path);
}
