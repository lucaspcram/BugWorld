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
    int lives;
};

int const G_PLAYER_MAX_STAM = 10;
int const G_PLAYER_MAX_DECOY = 3;
int const G_PLAYER_MAX_LIVES = 3;

/* Anim params */
/***************/
static int const G_PLAYER_WIDTH = 1;
static int const G_PLAYER_HEIGHT = 1;
static int const G_ANIM_TIMER = 1000;

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

    new_player->psprite = create_sprite(col, row, G_PLAYER_WIDTH, G_PLAYER_HEIGHT);
    new_player->stamina = G_PLAYER_MAX_STAM;
    new_player->decoys = G_PLAYER_MAX_DECOY;
    set_anim_params(new_player->psprite, 0, 0, G_ANIM_TIMER);
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

void render_player(struct player const * p)
{
    if (p == NULL)
        return;

    render_sprite(p->psprite, M_MAGENTA);
}

struct sprite * player_get_sprite(struct player const * p)
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

bool player_has_stamina(struct player const * p)
{
    if (p == NULL)
        return false;

    return p->stamina != 0;
}

void player_reset_stamina(struct player * p)
{
    if (p == NULL)
        return;

    p->stamina = G_PLAYER_MAX_STAM;
}

void player_inc_stamina(struct player * p)
{
    if (p == NULL)
        return;

    if (p->stamina >= G_PLAYER_MAX_STAM)
        return;

    p->stamina = p->stamina + 1;
}

int player_get_col(struct player const * p)
{
    if (p == NULL)
        return -1;

    return sprite_col(player_get_sprite(p));
}

int player_get_row(struct player const * p)
{
    if (p == NULL)
        return -1;

    return sprite_row(player_get_sprite(p));
}

void player_set_pos(struct player * p, int new_col, int new_row)
{
    if (p == NULL)
        return;

    sprite_set_col(player_get_sprite(p), new_col);
    sprite_set_row(player_get_sprite(p), new_row);
}
