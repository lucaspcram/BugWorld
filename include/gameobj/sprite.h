#ifndef SPRITE_H
#define SPRITE_H

/*
 * Sprites are NxM rectangles made of animated ASCII characters.
 */

struct sprite;

struct sprite * create_sprite(int col, int row, int width, int height);
void destroy_sprite(struct sprite * s);

void tick_sprite(struct sprite * s);
void render_sprite(struct sprite * s, int color);
void set_anim_params(struct sprite * s, int anim_state, int anim_timer, int timer_reset);

// see comment in sprite.c for format of 'frames' array
void set_frames(struct sprite * s, char const ** frames, int frames_len);

#endif
