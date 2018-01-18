#include "states/play_state.h"

#include "common.h"
#include "gameobj/player.h"
#include "gameobj/sprite.h"
#include "key_bindings.h"
#include "states/state_codes.h"
#include "view.h"
#include "world/world.h"

#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

static int const G_PLAYER_STARTING_SCORE = 0;
static int const G_PLAYER_STARTING_LIVES = 3;
static uint64_t const G_FRAME_TIME_NSEC = 500000000;

static struct world * g_world = NULL;
static int g_player_score;
static int g_player_lives;

static uint64_t g_anim_timer = 0;
static bool g_anim_frame = false;

int play_state_init(void)
{
    if (g_world == NULL)
        g_world = create_world();
    g_player_score = G_PLAYER_STARTING_SCORE;
    g_player_lives = G_PLAYER_STARTING_LIVES;

    return 0;
}

int play_state_destroy(void)
{
    destroy_world(g_world);
    return 0;
}

int play_state_pause(void)
{
    return 0;
}

int play_state_resume(void)
{
    return 0;
}

void play_state_tick(uint64_t elapsed)
{
    tick_world(g_world, elapsed);
    g_anim_timer += elapsed;
    if (g_anim_timer > G_FRAME_TIME_NSEC) {
        g_anim_timer = 0;
        g_anim_frame = !g_anim_frame;
    }
}

void play_state_handle_input(int input)
{
    if (input == M_MENU_QUIT)
        force_exit();

    handle_input_world(g_world, input);

    if (world_is_complete(g_world)) {
        g_player_score += world_getscore(g_world);
        init_state(M_STATE_GOAL);
        destroy_world(g_world);
        g_world = create_world();
    }

    if (world_is_playerdead(g_world)) {
        pthread_mutex_unlock(&g_ncurses_mut);
        sleep(1);
        pthread_mutex_lock(&g_ncurses_mut);
        g_player_lives -= 1;
        if (g_player_lives == 0) {
            /* TODO game over screen, save high score */
            init_state(M_STATE_OVER);
        } else {
            init_state(M_STATE_DEAD);
            destroy_world(g_world);
            g_world = create_world();
        }
    }
}

void play_state_render(void)
{
    /* 
    NOTE this function makes use of
    a lot of magic numbers in order to
    get the UI to look good on a 80x24 terminal
    */
    int i;
    char buf[32];

    struct player const * p = get_player(g_world);
    int const p_decoys = player_get_decoys(p);
    int const p_stamina = player_get_stamina(p);
    int const s_offset = M_SCRWIDTH - 24;

    render_world(g_world);

    /* Draw the stamina bar */
    snprintf(buf, sizeof(buf), "%d", p_stamina);
    draw_str("[S]", s_offset - 3, M_SCRHEIGHT - 2, M_MAGENTA);
    draw_str("|", s_offset, M_SCRHEIGHT - 2, M_MAGENTA);
    for (i = 1; i <= p_stamina * 2; i += 2)
        draw_str("==", s_offset + i, M_SCRHEIGHT - 2, M_MAGENTA);
    draw_str("|",
             s_offset + G_PLAYER_MAX_STAM * 2 + 1, M_SCRHEIGHT - 2, M_MAGENTA);
    draw_str(buf,
             s_offset + G_PLAYER_MAX_STAM * 2 + 2, M_SCRHEIGHT - 2, M_MAGENTA);

    /* Draw the decoy bar */
    draw_str("[D]", s_offset - 3, M_SCRHEIGHT - 1, M_MAGENTA);

    /* Draw the score */
    draw_str("[Score]", 0, M_SCRHEIGHT - 2, M_MAGENTA);
    snprintf(buf, sizeof(buf), "%d", g_player_score);
    draw_str(buf, 8, M_SCRHEIGHT - 2, M_MAGENTA);

    /* Draw remaining lives */
    draw_str("[Lives]", 0, M_SCRHEIGHT - 1, M_MAGENTA);
    if (g_anim_frame) {
        for (i = 0; i < g_player_lives; i++) {
            draw_str("X", 8 + i, M_SCRHEIGHT - 1, M_MAGENTA);
        }
    } else {
        for (i = 0; i < g_player_lives; i++) {
            draw_str("x", 8 + i, M_SCRHEIGHT - 1, M_MAGENTA);
        }
    }
}
