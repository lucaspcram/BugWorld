#include "states/seed_state.h"

#include "common.h"
#include "key_bindings.h"
#include "states/state_codes.h"
#include "view.h"

#define M_BUFSIZE (8)

static int const G_MAX_CHARS = 4;

static char g_buf[M_BUFSIZE];
static int g_index;

int seed_state_init(void)
{
    int i;

    g_index = 0;
    for(i = 0; i < M_BUFSIZE; i++)
        g_buf[i] = '\0';
    return 0;
}

int seed_state_destroy(void)
{
    return 0;
}

int seed_state_pause(void)
{
    return 0;
}

int seed_state_resume(void)
{
    return 0;
}

void seed_state_tick(uint64_t elapsed)
{

}

void seed_state_handle_input(int input)
{
    if (input == M_MENU_SELECT) {
        change_state(M_EXIT_DESTROY, M_START_INIT, M_STATE_PLAY);
    } else if (input >= '0' && input <= '9') {
        if (g_index < G_MAX_CHARS) {
            g_buf[g_index] = input;
            g_index += 1;
        }
    }
}

void seed_state_render(void)
{
    char buf[32];

    snprintf(buf, sizeof(buf), "%s", g_buf);
    draw_str(buf, 8, 8, M_WHITE);
}

void seed_state_recv_msg(void * msg)
{

}
