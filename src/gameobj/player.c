#include "gameobj/player.h"

#include "common.h"
#include "gameobj/sprite.h"
#include "view.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct player {
    struct sprite * psprite;
    int stamina;
    int decoys;
};

/* Anim params */
/***************/
#define M_PLAYER_WIDTH (1)
#define M_PLAYER_HEIGHT (1)
#define M_ANIM_TIMER (1000)

static const char * G_FRAMES[] = {
    "X",
    "x"
};
static const int G_FRAMES_LEN = 2;
/******END SECTION******/

struct player * create_player(int col, int row)
{
    struct player * new_player;
    new_player = M_SAFEMALLOC(sizeof(*new_player));

    new_player->psprite = create_sprite(col, row, M_PLAYER_WIDTH, M_PLAYER_HEIGHT);
    new_player->stamina = M_MAX_STAMINA;
    new_player->decoys = M_MAX_DECOYS;
    set_anim_params(new_player->psprite, 0, 0, M_ANIM_TIMER);
    set_frames(new_player->psprite, G_FRAMES, G_FRAMES_LEN);

    return new_player;
}

void destroy_player(struct player * p)
{
    if (p == NULL)
        return;

    destroy_sprite(p->psprite);
    free(p);
}

void tick_player(struct player * p, uint64_t elapsed)
{
    if (p == NULL)
        return;

    tick_sprite(p->psprite, elapsed);
}

void render_player(struct player * p)
{
    if (p == NULL)
        return;

    render_sprite(p->psprite, M_MAGENTA);
}

struct sprite * player_get_sprite(struct player * p)
{
    if (p == NULL)
        return NULL;

    return p->psprite;
}

int player_get_stamina(struct player const * p) {
    if (p == NULL) {
        return -1;
    }

    return p->stamina;
}

int player_get_decoys(struct player const * p) {
    if (p == NULL) {
        return -1;
    }

    return p->decoys;
}

void player_deplete_stamina(struct player * p)
{
    if (p == NULL)
        return;

    if (p->stamina <= 0)
        return;

    p->stamina = p->stamina - 1;
}

bool player_has_stamina(struct player * p)
{
    if (p == NULL)
        return false;

    return p->stamina != 0;
}

void player_reset_stamina(struct player * p)
{
    if (p == NULL)
        return;

    p->stamina = M_MAX_STAMINA;
}

void player_inc_stamina(struct player * p)
{
    if (p == NULL)
        return;

    if (p->stamina >= M_MAX_STAMINA)
        return;

    p->stamina = p->stamina + 1;
}
