#include "world/map.h"

#include "common.h"
#include "gameobj/sprite.h"
#include "view.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define M_TILE_WIDTH (1)
#define M_TILE_HEIGHT (1)

#define M_GRASS_TIMER (700)
#define M_WATER_TIMER (300)
#define M_MOUND_TIMER (800)
#define M_GOAL_TIMER (1000)


static const char * G_GRASS_FRAMES[] = {
    "\\",
    "|",
    "/",
    "|"
};
static const int G_GRASS_FRAMES_LEN = 4;
static const char * G_WATER_FRAMES[] = {
    "~",
    "="
};
static const int G_WATER_FRAMES_LEN = 2;
static const char * G_MOUND_FRAMES[] = {
    "M",
    "m"
};
static const int G_MOUND_FRAMES_LEN = 2;
static const char * G_GOAL_FRAMES[] = {
    "O"
};
static const int G_GOAL_FRAMES_LEN = 1;

struct map {
    int rows;
    int cols;

    /* 
    Reuse the same 4 sprite objects across the map.
    Keeps the code simpler, but loses the ability to
    have decoupled animations across map surface.
    */
    struct sprite * grass_spr;
    struct sprite * water_spr;
    struct sprite * mound_spr;
    struct sprite * goal_spr;

    enum tile_type ** tiles;
};

struct map * create_map(int row, int col)
{
    struct map * new_map;
    enum tile_type ** new_tiles;
    int i;
    int j;
    
    new_map = M_SAFEMALLOC(sizeof(struct map));
    new_map->rows = row;
    new_map->cols = col;

    new_tiles = M_SAFEMALLOC(sizeof(*new_tiles) * row);
    for (i = 0; i < row; i++)
        new_tiles[i] = M_SAFEMALLOC(sizeof(*new_tiles[i]) * col);

    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            new_tiles[i][j] = E_EMPTY;

    new_map->tiles = new_tiles;

    // initialize the tile sprites
    new_map->grass_spr = create_sprite(0, 0, M_TILE_WIDTH, M_TILE_HEIGHT);
    set_anim_params(new_map->grass_spr, 0, 0, M_GRASS_TIMER);
    set_frames(new_map->grass_spr, G_GRASS_FRAMES, G_GRASS_FRAMES_LEN);

    new_map->water_spr = create_sprite(0, 0, M_TILE_WIDTH, M_TILE_HEIGHT);
    set_anim_params(new_map->water_spr, 0, 0, M_WATER_TIMER);
    set_frames(new_map->water_spr, G_WATER_FRAMES, G_WATER_FRAMES_LEN);

    new_map->mound_spr = create_sprite(0, 0, M_TILE_WIDTH, M_TILE_HEIGHT);
    set_anim_params(new_map->mound_spr, 0, 0, M_MOUND_TIMER);
    set_frames(new_map->mound_spr, G_MOUND_FRAMES, G_MOUND_FRAMES_LEN);

    new_map->goal_spr = create_sprite(0, 0, M_TILE_WIDTH, M_TILE_HEIGHT);
    set_anim_params(new_map->goal_spr, 0, 0, M_GOAL_TIMER);
    set_frames(new_map->goal_spr, G_GOAL_FRAMES, G_GOAL_FRAMES_LEN);

    return new_map;
}

void destroy_map(struct map * m)
{
    int i;

    if (m == NULL)
        return;

    for (i = 0; i < m->rows; i++)
        free(m->tiles[i]);
    free(m->tiles);

    destroy_sprite(m->grass_spr);
    destroy_sprite(m->water_spr);
    destroy_sprite(m->mound_spr);
    destroy_sprite(m->goal_spr);

    free(m);
}

void tick_map(struct map * m, uint64_t elapsed)
{
    if (m == NULL)
        return;

    tick_sprite(m->grass_spr, elapsed);
    tick_sprite(m->water_spr, elapsed);
    tick_sprite(m->mound_spr, elapsed);
    tick_sprite(m->goal_spr, elapsed);
}

void render_map(struct map const * m)
{
    int i;
    int j;
    
    if (m == NULL)
        return;

    for (i = 0; i < m->rows; i++) {
        for (j = 0; j < m->cols; j++) {
            switch(m->tiles[i][j]) {
                case E_EMPTY:
                    draw('.', j, i, M_YELLOW);
                    break;
                case E_GRASS:
                    M_SET_SPRITE_POS(m->grass_spr, j, i);
                    render_sprite(m->grass_spr, M_GREEN);
                    break;
                case E_WATER:
                    M_SET_SPRITE_POS(m->water_spr, j, i);
                    render_sprite(m->water_spr, M_CYAN);
                    break;
                case E_MOUND:
                    M_SET_SPRITE_POS(m->mound_spr, j, i);
                    render_sprite(m->mound_spr, M_YELLOW);
                    break;
                case E_GOAL:
                    M_SET_SPRITE_POS(m->goal_spr, j, i);
                    render_sprite(m->goal_spr, M_MAGENTA);
                    break;
            }
        }
    }
}

int map_rows(struct map const * m) {
    if (m == NULL)
        return -1;

    return m->rows;
}

int map_cols(struct map const * m) {
    if (m == NULL)
        return -1;

    return m->cols;
}

bool map_is_valid_tile(struct map const * m, int col, int row)
{
    if (m == NULL)
        return false;

    if (col < 0 || col >= m->cols)
        return false;
    if (row < 0 || row >= m->rows)
        return false;

    return true;
}

void map_set(struct map * m, int i, int j, enum tile_type tile)
{
    if (m == NULL)
        return;

    m->tiles[i][j] = tile;
}

bool map_point_hastype(struct map const * m,
                       int col, int row,
                       enum tile_type tile)
{
    return m->tiles[row][col] == tile;
}

