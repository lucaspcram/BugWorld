#include "states/help_state.h"

#include "common.h"
#include "key_bindings.h"
#include "states/state_codes.h"
#include "view.h"

#include <stdint.h>

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
    if (input == M_MENU_QUIT) {
        change_state(M_EXIT_DESTROY, M_START_INIT, M_STATE_MENU);
    }

    if (input == M_MENU_SELECT) {
        change_state(M_EXIT_DESTROY, M_START_INIT, M_STATE_MENU);
    }
}

void help_state_render(void)
{

}

void help_state_recv_msg(void * msg)
{

}
