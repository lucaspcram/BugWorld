#ifndef GRASS_H
#define GRASS_H

struct grass {
	int col;
	int row;
	int width;
	int height;
	int anim_state;
	int anim_timer;
};

struct grass * create_grass(int col, int row, int width, int height);
void destroy_grass(struct grass * g);

void update_grass(struct grass * g);
void render_grass(struct grass * g);

#endif
