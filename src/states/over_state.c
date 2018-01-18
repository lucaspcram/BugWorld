#include "states/over_state.h"

#include "states/state_codes.h"
#include "view.h"

#include <stdint.h>

static uint64_t const G_STATE_TIMER_NSEC = 5000000000;

static uint64_t g_timer;

int over_state_init(void)
{
    g_timer = 0;
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
    if (g_timer > G_STATE_TIMER_NSEC) {
        /* TODO acquire and save the high score */
        force_exit();
    }
    g_timer += elapsed;
}

void over_state_handle_input(int input)
{

}

void over_state_render(void)
{
    draw_str("Game over! TODO fix this", 2, 2, M_MAGENTA);
}
