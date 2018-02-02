#include "states/score_state.h"

#include "common.h"
#include "key_bindings.h"
#include "scores.h"
#include "states/state_codes.h"
#include "view.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static char const * G_FRAME1[] =
{
"  /######   /######   /######  /#######  /########  /###### ",
" /##__  ## /##__  ## /##__  ##| ##__  ##| ##_____/ /##__  ##",
"| ##  \\__/| ##  \\__/| ##  \\ ##| ##  \\ ##| ##      | ##  \\__/",
"|  ###### | ##      | ##  | ##| #######/| #####   |  ###### ",
" \\____  ##| ##      | ##  | ##| ##__  ##| ##__/    \\____  ##",
" /##  \\ ##| ##    ##| ##  | ##| ##  \\ ##| ##       /##  \\ ##",
"|  ######/|  ######/|  ######/| ##  | ##| ########|  ######/",
" \\______/  \\______/  \\______/ |__/  |__/|________/ \\______/ "
};

static char const * G_FRAME2[] =
{
"  /******   /******   /******  /*******  /********  /****** ",
" /**__  ** /**__  ** /**__  **| **__  **| **_____/ /**__  **",
"| **  \\__/| **  \\__/| **  \\ **| **  \\ **| **      | **  \\__/",
"|  ****** | **      | **  | **| *******/| *****   |  ****** ",
" \\____  **| **      | **  | **| **__  **| **__/    \\____  **",
" /**  \\ **| **    **| **  | **| **  \\ **| **       /**  \\ **",
"|  ******/|  ******/|  ******/| **  | **| ********|  ******/",
" \\______/  \\______/  \\______/ |__/  |__/|________/ \\______/ "
};
static int const G_FRAME_LEN = 8;
static int const G_TITLE_COL_OFFSET = 10;
static int const G_TITLE_ROW_OFFSET = 1;

static int const G_SCORELIST_COL_OFF = 25;
static int const G_SCORELIST_ROW_OFF = 12;
static int const G_LIST_CUTOFF = 8;
static int const G_MS_UPDATETIMER = 500;

static int g_anim_timer;
static int g_anim_state;

static struct score ** g_scores;

int score_state_init(void)
{
    char * sfile;

    sfile = create_scorefile();
    g_scores = read_scorefile(sfile);
    sort_scores(g_scores);

    return 0;
}

int score_state_destroy(void)
{
    free_scorelist(g_scores);
    return 0;
}

int score_state_pause(void)
{
    return 0;
}

int score_state_resume(void)
{
    return 0;
}

void score_state_tick(uint64_t elapsed)
{
    g_anim_timer += elapsed;
    if (g_anim_timer >= ms2ns(G_MS_UPDATETIMER)) {
        g_anim_timer = 0;
        g_anim_state = !g_anim_state;
    }
}

void score_state_handle_input(int input)
{
    if (input == M_MENU_QUIT) {
        change_state(M_EXIT_DESTROY, M_START_INIT, M_STATE_MENU);
    }

    if (input == M_MENU_SELECT) {
        change_state(M_EXIT_DESTROY, M_START_INIT, M_STATE_MENU);
    }
}

void score_state_render(void)
{
#define M_SCORESTR_LEN (128)
    int i;
    struct score ** tmp;
    char buf[M_SCORESTR_LEN];
    char const * help_hint = "Q or ENTER to return to menu";
    int hint_len = strlen(help_hint);

    for (i = 0; i < G_FRAME_LEN; i++) {
        if (g_anim_state == 0)
            draw_str(G_FRAME1[i],
                     G_TITLE_COL_OFFSET, G_TITLE_ROW_OFFSET + i, M_CYAN);
        else
            draw_str(G_FRAME2[i],
                     G_TITLE_COL_OFFSET, G_TITLE_ROW_OFFSET + i, M_CYAN);
    }

    tmp = g_scores;
    if (tmp == NULL)
        return;

    i = 0;
    draw_str("SCORE  |  LEVELS CLEARED",
             G_SCORELIST_COL_OFF + 7, G_SCORELIST_ROW_OFF - 1, M_CYAN);
    while (*tmp != NULL) {
        snprintf(buf, sizeof(buf), "%d. %9d  |  %9d",
                 i + 1, (*tmp)->score, (*tmp)->levels_cleared);
        draw_str(buf, G_SCORELIST_COL_OFF, G_SCORELIST_ROW_OFF + i, M_CYAN);
        tmp++;
        i++;
        if (i >= G_LIST_CUTOFF)
            return;
    }

    while (i < G_LIST_CUTOFF) {
        snprintf(buf, sizeof(buf), "%d. %9s  |  %9s", i + 1, "-", "-");
        draw_str(buf, G_SCORELIST_COL_OFF, G_SCORELIST_ROW_OFF + i, M_CYAN);
        i++;
    }

    draw_str(help_hint,
            (M_SCRWIDTH / 2) - (hint_len / 2), M_SCRHEIGHT - 1,
             M_CYAN);
#undef M_SCORESTR_LEN
}

void score_state_recv_msg(void * msg)
{

}

