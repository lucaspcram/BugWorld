#include "states/goal_state.h"

#include "states/state_codes.h"
#include "view.h"

#include <stdint.h>

static uint64_t const G_STATE_TIMER_NSEC = 4000000000;

static uint64_t g_timer;

int goal_state_init(void)
{
    g_timer = 0;
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
    if (g_timer > G_STATE_TIMER_NSEC)
        resume_state(M_STATE_PLAY);
    g_timer += elapsed;
}

void goal_state_handle_input(int input)
{

}

void goal_state_render(void)
{
    draw_str("Yay you goaled! TODO fix this", 2, 2, M_MAGENTA);
}
