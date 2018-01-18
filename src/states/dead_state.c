#include "states/dead_state.h"

#include "states/state_codes.h"
#include "view.h"

#include <stdint.h>

static uint64_t const G_STATE_TIMER_NSEC = 4000000000;

static uint64_t g_timer;

int dead_state_init(void)
{
    g_timer = 0;
    return 0;
}

int dead_state_destroy(void)
{
    return 0;
}

int dead_state_pause(void)
{
    return 0;
}

int dead_state_resume(void)
{
    return 0;
}

void dead_state_tick(uint64_t elapsed)
{
    if (g_timer > G_STATE_TIMER_NSEC)
        resume_state(M_STATE_PLAY);
    g_timer += elapsed;
}

void dead_state_handle_input(int input)
{

}

void dead_state_render(void)
{
    draw_str("You died! TODO make this better", 2, 2, M_MAGENTA);
}
