#include "goal_state.h"

#include "common.h"
#include "key_bindings.h"
#include "state_codes.h"
#include "view.h"

#include <stdint.h>
#include <string.h>

static char const * G_FRAME1[] =
{
"  /######   /######   /######  /##       /##",
" /##__  ## /##__  ## /##__  ##| ##      | ##",
"| ##  \\__/| ##  \\ ##| ##  \\ ##| ##      | ##",
"| ## /####| ##  | ##| ########| ##      | ##",
"| ##|_  ##| ##  | ##| ##__  ##| ##      |__/",
"| ##  \\ ##| ##  | ##| ##  | ##| ##          ",
"|  ######/|  ######/| ##  | ##| ######## /##",
" \\______/  \\______/ |__/  |__/|________/|__/"
};
static char const * G_FRAME2[] =
{
"  /******   /******   /******  /**       /**",
" /**__  ** /**__  ** /**__  **| **      | **",
"| **  \\__/| **  \\ **| **  \\ **| **      | **",
"| ** /****| **  | **| ********| **      | **",
"| **|_  **| **  | **| **__  **| **      |__/",
"| **  \\ **| **  | **| **  | **| **          ",
"|  ******/|  ******/| **  | **| ******** /**",
" \\______/  \\______/ |__/  |__/|________/|__/"
};
static int const G_FRAME_LEN = 8;
static int const G_TITLE_ROW_OFFSET = 4;

static int const G_MS_UPDATETIMER = 500;

static int g_anim_timer;
static int g_anim_state;

int goal_state_init(void)
{
    return 0;
}

int goal_state_destroy(void)
{
    return 0;
}

int goal_state_pause(void)
{
    return 0;
}

int goal_state_resume(void)
{
    return 0;
}

void goal_state_tick(uint64_t elapsed)
{
    g_anim_timer += elapsed;
    if (g_anim_timer >= ms2ns(G_MS_UPDATETIMER)) {
        g_anim_timer = 0;
        g_anim_state = !g_anim_state;
    }
}

void goal_state_handle_input(int input)
{
    if (input == M_MENU_SELECT)
        change_state(M_EXIT_DESTROY, M_START_RESUME, M_STATE_PLAY);

    if (input == M_MENU_QUIT)
        force_exit();
}

void goal_state_render(void)
{
    int i;
    char const * help_hint = "ENTER to continue";
    int hint_len = strlen(help_hint);

    for (i = 0; i < G_FRAME_LEN; i++) {
        if (g_anim_state == 0)
            draw_str(G_FRAME1[i], 20, G_TITLE_ROW_OFFSET + i, M_CYAN);
        else
            draw_str(G_FRAME2[i], 20, G_TITLE_ROW_OFFSET + i, M_CYAN);
    }

    draw_str(help_hint,
            (M_SCRWIDTH / 2) - (hint_len / 2), M_SCRHEIGHT - 1,
             M_CYAN);
}

void goal_state_recv_msg(void * msg)
{
    
}
