#include "gameobj/enemy.h"

#include "common.h"
#include "gameobj/sprite.h"
#include "world/map.h"
#include "view.h"

#include <float.h>
#include <stdint.h>
#include <stdlib.h>

struct enemy {
    struct sprite * esprite;
};

static const char * G_FRAMES[] = {
    "v",
    "V"
};
static const int G_FRAMES_LEN = 2;
/******END SECTION******/

/* Anim params */
/***************/
#define M_ENEMY_WIDTH (1)
#define M_ENEMY_HEIGHT (1)
#define M_ANIM_TIMER (1000)

struct enemy * create_enemy(int col, int row)
{
    struct enemy * new_enemy;
    new_enemy = M_SAFEMALLOC(sizeof(*new_enemy));

    new_enemy->esprite = create_sprite(col, row, M_ENEMY_WIDTH, M_ENEMY_HEIGHT);
    set_anim_params(new_enemy->esprite, 0, 0, M_ANIM_TIMER);
    set_frames(new_enemy->esprite, G_FRAMES, G_FRAMES_LEN);

    return new_enemy;
}

void destroy_enemy(struct enemy * e)
{
    if (e == NULL)
        return;

    destroy_sprite(e->esprite);
    free(e);
}

void tick_enemy(struct enemy * e, uint64_t elapsed)
{
    if (e == NULL)
        return;

    tick_sprite(e->esprite, elapsed);
}

void render_enemy(struct enemy * e)
{
    if (e == NULL)
        return;

    render_sprite(e->esprite, M_RED);
}

void act_enemy(struct enemy * e, struct map const * m, int pl_c, int pl_r)
{
    /* Cardinal directions for enemy movement */
    #define M_NUM_CARDINALS (8)

    int i;
    int enem_c;
    int enem_r;
    int mov_c;
    int mov_r;
    int min_index;
    struct vec2d moves[M_NUM_CARDINALS];
    double move_vals[M_NUM_CARDINALS];
    double min_sofar;

    int const col_mov[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int const row_mov[] = {1, 1, 0, -1, -1, -1, 0, 1};

    /* Player is invisible while in grass */
    if (map_point_hastype(m, pl_c, pl_r, E_GRASS))
        return;

    enem_c = sprite_col(e->esprite);
    enem_r = sprite_row(e->esprite);

    /*
    Calculate vector values for the 8 possible moves each enemy can
    make. Always try to move closer to the player while avoiding water.
    */
    for (i = 0; i < M_NUM_CARDINALS; i++) {
        mov_c = enem_c + col_mov[i];
        mov_r = enem_r + row_mov[i];
        if (map_is_valid_tile(m, mov_c, mov_r)) {
            if (map_point_hastype(m, mov_c, mov_r, E_WATER)) {
                moves[i].x = 0;
                moves[i].y = 0;
                move_vals[i] = DBL_MAX;
            } else {
                moves[i].x = pl_c - mov_c;
                moves[i].y = pl_r - mov_r;
                move_vals[i] = vec2d_magn(&moves[i]);
            }
        } else {
            moves[i].x = 0;
            moves[i].y = 0;
            move_vals[i] = DBL_MAX;
        }
    }

    /* Pick that vector that leaves the enemy closest to the player */
    min_sofar = DBL_MAX;
    for (i = 0; i < M_NUM_CARDINALS; i++) {
        if (move_vals[i] < min_sofar) {
            min_sofar = move_vals[i];
            min_index = i;
        }
    }

    M_SET_SPRITE_POS(e->esprite,
                     enem_c + col_mov[min_index], enem_r + row_mov[min_index]);

    #undef M_NUM_CARDINALS
}
