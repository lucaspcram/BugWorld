#include "states/seed_state.h"

#include "common.h"
#include "key_bindings.h"
#include "states/state_codes.h"
#include "view.h"

int seed_state_init(void)
{
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
    }
}

void seed_state_render(void)
{

}

void seed_state_recv_msg(void * msg)
{

}
