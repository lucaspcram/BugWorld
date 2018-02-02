#include "states/help_state.h"

#include "common.h"
#include "key_bindings.h"
#include "states/state_codes.h"
#include "view.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int const G_COL = 3;
static int const G_ROW = 1;

int help_state_init(void)
{
    return 0;
}

int help_state_destroy(void)
{
    return 0;
}

int help_state_pause(void)
{
    return 0;
}

int help_state_resume(void)
{
    return 0;
}

void help_state_tick(uint64_t elapsed)
{

}

void help_state_handle_input(int input)
{
    if (input == M_MENU_QUIT)
        change_state(M_EXIT_DESTROY, M_START_INIT, M_STATE_MENU);

    if (input == M_MENU_SELECT)
        change_state(M_EXIT_DESTROY, M_START_INIT, M_STATE_MENU);
}

void help_state_render(void)
{
    char const * help_hint = "Q or ENTER to return to menu";
    int hint_len = strlen(help_hint);

    draw_str("Controls: WASD to move, E to rest, F to drop decoy, Q to quit, B for boss",
             G_COL, G_ROW, M_WHITE);
    draw_str("Basic Rules: Reach the goal to score points! Ants track your",
             G_COL, G_ROW + 2, M_WHITE);
    draw_str("every move unless you stay hidden in the tall grass. You can",
             G_COL, G_ROW + 3, M_WHITE);
    draw_str("swim - unlike the ants - but you cannot pass the anthills.",
             G_COL, G_ROW + 4, M_WHITE);
    draw_str("If your stamina runs out while exposed, you can restore some",
             G_COL, G_ROW + 5, M_WHITE);
    draw_str("by resting. But be careful, ants will track you while you rest",
             G_COL, G_ROW + 6, M_WHITE);
    draw_str("and you cannot rest while swimming. Running out of stamina on",
             G_COL, G_ROW + 7, M_WHITE);
    draw_str("the water is deadly! You can also deploy a decoy for a limited",
             G_COL, G_ROW + 8, M_WHITE);
    draw_str("time (using both forfeits your points for that stage), and ants",
             G_COL, G_ROW + 9, M_WHITE);
    draw_str("will track it instead of you while it remains active.",
             G_COL, G_ROW + 10, M_WHITE);

    draw_str("X", G_COL, G_ROW + 12, M_MAGENTA);
    draw_str(" - player", G_COL + 1, G_ROW + 12, M_WHITE);

    draw_str("#", G_COL, G_ROW + 13, M_MAGENTA);
    draw_str(" - decoy", G_COL + 1, G_ROW + 13, M_WHITE);

    draw_str("G", G_COL, G_ROW + 14, M_MAGENTA);
    draw_str(" - goal", G_COL + 1, G_ROW + 14, M_WHITE);

    draw_str("V", G_COL, G_ROW + 15, M_RED);
    draw_str(" - ant", G_COL + 1, G_ROW + 15, M_WHITE);

    draw_str("M", G_COL, G_ROW + 16, M_YELLOW);
    draw_str(" - anthill", G_COL + 1, G_ROW + 16, M_WHITE);

    draw_str("\\|/", G_COL, G_ROW + 17, M_GREEN);
    draw_str(" - tall grass", G_COL + 3, G_ROW + 17, M_WHITE);

    draw_str("~=", G_COL, G_ROW + 18, M_CYAN);
    draw_str(" - water", G_COL + 2, G_ROW + 18, M_WHITE);

    draw_str(help_hint,
            (M_SCRWIDTH / 2) - (hint_len / 2), M_SCRHEIGHT - 1,
             M_CYAN);
}

void help_state_recv_msg(void * msg)
{

}
