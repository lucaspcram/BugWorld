#include "world/world.h"

#include "common.h"
#include "gameobj/enemy.h"
#include "gameobj/player.h"
#include "gameobj/sprite.h"
#include "key_bindings.h"
#include "world/map.h"
#include "world/world_gen.h"
#include "view.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* oversize for safety */
#define M_ENEMIES_SIZE (32)

static int num_enemies = 0;

struct world {
    struct player * player;
    struct map * map;
    struct enemy ** enemies;
    bool world_complete;
};

static void attempt_player_move(struct player * p, struct map * map,
                                int p_newcol, int p_newrow, bool * update_enem);

struct world * create_world(void)
{
    struct world * new_world;

    /* Must generate the map before the entities */
    new_world = M_SAFEMALLOC(sizeof(struct world));
    new_world->map = create_map(M_SCRHEIGHT - 2, M_SCRWIDTH);
    fill_map(new_world->map);

    spawn_player(&(new_world->player), new_world->map);
    spawn_goal(new_world->map);
    spawn_mounds(new_world->map);
    new_world->enemies = M_SAFEMALLOC(M_ENEMIES_SIZE * sizeof(struct enemy *));
    num_enemies = spawn_enemies(new_world->enemies, new_world->map);

    new_world->world_complete = false;

    return new_world;
}

void destroy_world(struct world * w)
{
    if (w == NULL)
        return;

    destroy_player(w->player);
    destroy_map(w->map);
    M_FOR_ALL_ELEMENTS(w->enemies, num_enemies, destroy_enemy);
    free(w->enemies);
    free(w);
}

void handle_input_world(struct world * w, int input)
{
    int p_col;
    int p_row;
    bool update_enem = false;

    if (w == NULL)
        return;

    p_col = player_get_col(w->player);
    p_row = player_get_row(w->player);

    if (input == M_ACTION_UP && player_has_stamina(w->player)) {
        attempt_player_move(w->player, w->map, p_col, p_row - 1, &update_enem);
    }
    if (input == M_ACTION_DOWN && player_has_stamina(w->player)) {
        attempt_player_move(w->player, w->map, p_col, p_row + 1, &update_enem);
    }
    if (input == M_ACTION_LEFT && player_has_stamina(w->player)) {
        attempt_player_move(w->player, w->map, p_col - 1, p_row, &update_enem);
    }
    if (input == M_ACTION_RIGHT && player_has_stamina(w->player)) {
        attempt_player_move(w->player, w->map, p_col + 1, p_row, &update_enem);
    }
    if (input == M_ACTION_REST) {
        player_inc_stamina(w->player);
        update_enem = true;
    }

    if (update_enem) {
        M_FOR_ALL_ELEMENTS_EXT(w->enemies, num_enemies,
                               act_enemy, w->map,
                               player_get_col(w->player),
                               player_get_row(w->player));
        update_enem = false;
    }

    if (map_point_hastype(w->map,
                          player_get_col(w->player),
                          player_get_row(w->player),
                          E_GRASS))
    {
        player_reset_stamina(w->player);
    }

    if (map_point_hastype(w->map,
                          player_get_col(w->player),
                          player_get_row(w->player),
                          E_GOAL))
    {
        w->world_complete = true;
    }
}

static void attempt_player_move(struct player * p, struct map * map,
                                int p_newcol, int p_newrow, bool * update_enem)
{
    int m_maxcol;
    int m_maxrow;

    m_maxcol = map_cols(map);
    m_maxrow = map_rows(map);

    if (p_newcol < 0 || p_newcol >= m_maxcol)
        return;
    if (p_newrow < 0 || p_newrow >= m_maxrow)
        return;

    if (!map_point_hastype(map,
                           p_newcol,
                           p_newrow,
                           E_MOUND))
    {
        player_set_pos(p, p_newcol, p_newrow);
    }
    player_deplete_stamina(p);
    *update_enem = true;
}

void tick_world(struct world * w, uint64_t elapsed)
{
    if (w == NULL)
        return;

    tick_player(w->player, elapsed);
    tick_map(w->map, elapsed);
    M_FOR_ALL_ELEMENTS_EXT(w->enemies, num_enemies, tick_enemy, elapsed);
}

void render_world(struct world const * w)
{
    if (w == NULL)
        return;

    render_map(w->map);
    render_player(w->player);
    M_FOR_ALL_ELEMENTS(w->enemies, num_enemies, render_enemy);
}

struct player * get_player(struct world const * w)
{
    if (w == NULL)
        return NULL;

    return w->player;
}

bool world_is_complete(struct world const * w)
{
    if (w == NULL)
        return false;

    return w->world_complete;
}
