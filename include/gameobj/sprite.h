#ifndef SPRITE_H
#define SPRITE_H

/*
 * Sprites are NxM rectangles made of animated ASCII characters.
 */

#define M_SET_SPRITE_POS(sprite, row, col) \
do {                                       \
sprite_set_row(sprite, row);               \
sprite_set_col(sprite, col);               \
} while(0)
 
struct sprite;

struct sprite * create_sprite(int col, int row, int width, int height);
void destroy_sprite(struct sprite * s);

void tick_sprite(struct sprite * s);
void render_sprite(struct sprite * s, int color);
void set_anim_params(struct sprite * s, int anim_state, int anim_timer, int timer_reset);

/* see comment in sprite.c for format of 'frames' array */
void set_frames(struct sprite * s, char const ** frames, int frames_len);

int sprite_row(struct sprite * s);
int sprite_col(struct sprite * s);

void sprite_set_row(struct sprite * s, int row);
void sprite_set_col(struct sprite * s, int col);

#endif
