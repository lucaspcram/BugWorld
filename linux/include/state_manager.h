#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

/*
 * The state manager suite. Interfaces the main game code
 * with the actual state code.
 *
 * NOTE This implementation has a design deficiency in that
 * it has no mechanism for information transfer between game states.
 * This would be a nice improvement and eliminate the need for a global
 * score variable.
 */

#include <stdbool.h>
#include <stdint.h>

bool exit_flag;

struct state {
    /* Lifecycle functions */
    int (*init)(void);
    int (*destroy)(void);
    int (*pause)(void);
    int (*resume)(void);

    /* State functions */
    void (*tick)(uint64_t elapsed);
    void (*handle_input)(int);
    void (*render)(void);

    /* RECV function */
    void (*recv_msg)(void *);
};

void init_state_manager(void);
void destroy_state_manager(void);
void handle_input(int input);
void tick_render(uint64_t elapsed);

#endif
