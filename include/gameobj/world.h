#ifndef WORLD_H
#define WORLD_H

/*
 * Container object for the in-game world. The world manages
 * the memory lifetimes of a player, enemies, and obstacles.
 * The world also manages generating new levels.
 */

struct world {
	struct player * player;
};

struct world * init_world(void);
void destroy_world(struct world * w);

void update_world(void);
void handle_input_world(struct world * world, int input);
void render_world(void);

#endif
