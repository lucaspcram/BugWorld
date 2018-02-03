#ifndef SEED_STATE_H
#define SEED_STATE_H

#include <stdint.h>

/*
 * Code for the seed entry game state.
 */

struct worldseed {
    int seed;
};

int seed_state_init(void);
int seed_state_destroy(void);
int seed_state_pause(void);
int seed_state_resume(void);
void seed_state_tick(uint64_t elapsed);
void seed_state_handle_input(int input);
void seed_state_render(void);
void seed_state_recv_msg(void * msg);

#endif
