#include "player.h"

#include "common.h"
#include "sprite.h"
#include "view.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct player {
    struct sprite * psprite;
    struct sprite * dsprite;
    int stamina;
    int decoys;
    int decoy_hp;
    int lives;
};

int const G_PLAYER_MAX_STAM = 10;
int const G_PLAYER_MAX_DECOY = 2;
int const G_PLAYER_MAX_DECOYHP = 21;

/* Anim params */
/***************/
static int const G_PLAYER_WIDTH = 1;
static int const G_PLAYER_HEIGHT = 1;
static int const G_ANIM_TIMER = 1000;

static const char * G_FRAMES[] = {
    "X",
    "x"
};
static int const G_FRAMES_LEN = 2;

static const char * G_FRAMESDEC[] = {
    "#"
};
static int const G_FRAMESDEC_LEN = 1;
/******END SECTION******/

static void player_deplete_decoy(struct player * p);

struct player * create_player(int col, int row)
{
    struct player * new_player;
    new_player = M_SAFEMALLOC(sizeof(*new_player));

    new_player->psprite = create_sprite(col, row, G_PLAYER_WIDTH, G_PLAYER_HEIGHT);
    new_player->dsprite = create_sprite(-1, -1, G_PLAYER_WIDTH, G_PLAYER_HEIGHT);
    new_player->stamina = G_PLAYER_MAX_STAM;
    new_player->decoys = G_PLAYER_MAX_DECOY;
    new_player->decoy_hp = 0;

    set_anim_params(new_player->psprite, 0, 0, G_ANIM_TIMER);
    set_frames(new_player->psprite, G_FRAMES, G_FRAMES_LEN);
    set_anim_params(new_player->dsprite, 0, 0, G_ANIM_TIMER);
    set_frames(new_player->dsprite, G_FRAMESDEC, G_FRAMESDEC_LEN);

    return new_player;
}

void destroy_player(struct player * p)
{
    if (p == NULL)
        return;

    destroy_sprite(p->psprite);
    destroy_sprite(p->dsprite);
    free(p);
}

void tick_player(struct player * p, uint64_t elapsed)
{
    if (p == NULL)
        return;

    tick_sprite(p->psprite, elapsed);
    tick_sprite(p->dsprite, elapsed);
}

void render_player(struct player const * p)
{
    if (p == NULL)
        return;

    render_sprite(p->psprite, M_MAGENTA);
    if (p->decoy_hp > 0)
        render_sprite(p->dsprite, M_MAGENTA);
}

struct sprite * player_get_sprite(struct player const * p)
{
    if (p == NULL)
        return NULL;

    return p->psprite;
}

int player_get_stamina(struct player const * p) {
    if (p == NULL)
        return -1;

    return p->stamina;
}

int player_get_decoys(struct player const * p) {
    if (p == NULL)
        return -1;

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

void player_deploy_decoy(struct player * p)
{
    int p_col;
    int p_row;

    if (p == NULL)
        return;

    if (p->decoys <= 0)
        return;

    if (p->decoy_hp > 0)
        return;

    p_col = sprite_col(p->psprite);
    p_row = sprite_row(p->psprite);
    sprite_set_col(p->dsprite, p_col);
    sprite_set_row(p->dsprite, p_row);
    player_deplete_decoy(p);
    p->decoy_hp = G_PLAYER_MAX_DECOYHP;
}

static void player_deplete_decoy(struct player * p)
{
    if (p == NULL)
        return;

    if (p->decoys <= 0)
        return;

    p->decoys = p->decoys - 1;
}

bool player_has_decoy(struct player const * p)
{
    if (p == NULL)
        return false;

    return p->decoys != 0;
}

void player_reset_decoy(struct player * p)
{
    if (p == NULL)
        return;

    p->decoys = G_PLAYER_MAX_DECOY;
}

void player_inc_decoy(struct player * p)
{
    if (p == NULL)
        return;

    if (p->decoys >= G_PLAYER_MAX_DECOY)
        return;

    p->decoys = p->decoys + 1;
}

bool player_decoy_deployed(struct player const * p)
{
    if (p == NULL)
        return false;

    return p->decoy_hp > 0;
}

void player_update_decoy(struct player * p)
{
    if (p == NULL)
        return;

    if (p->decoy_hp > 0)
        p->decoy_hp -= 1;
}

int player_get_col(struct player const * p)
{
    if (p == NULL)
        return -1;

    return sprite_col(p->psprite);
}

int player_get_row(struct player const * p)
{
    if (p == NULL)
        return -1;

    return sprite_row(p->psprite);
}

int player_get_deccol(struct player const * p)
{
    if (p == NULL)
        return -1;

    return sprite_col(p->dsprite);
}

int player_get_decrow(struct player const * p)
{
    if (p == NULL)
        return -1;

    return sprite_row(p->dsprite);
}

void player_set_pos(struct player * p, int new_col, int new_row)
{
    if (p == NULL)
        return;

    sprite_set_col(player_get_sprite(p), new_col);
    sprite_set_row(player_get_sprite(p), new_row);
}
