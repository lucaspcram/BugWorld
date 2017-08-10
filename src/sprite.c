#include "sprite.h"
#include "util.h"
#include "view.h"

#include <stdlib.h>
#include <string.h>

static void advance_state(struct sprite * s);

/* Lifecycle functions */
/***********************/
struct sprite * create_sprite(int col, int row, int width, int height)
{
	struct sprite * new_sprite;
	const int DEFAULT_TIMER_RESET = 45;

	new_sprite = (struct sprite *) malloc(sizeof(*new_sprite));
	if (new_sprite == NULL)
		abort_game("malloc failed in function \'create_sprite\'");

	new_sprite->col = col;
	new_sprite->row = row;
	new_sprite->width = width;
	new_sprite->height = height;
	new_sprite->anim_state = 0;
	new_sprite->anim_timer = 0;
	new_sprite->timer_reset = DEFAULT_TIMER_RESET;

	return new_sprite;
}

void destroy_sprite(struct sprite * s)
{
	if (s == NULL)
		return;

	free(s->frames);
	free(s);
}
/******END SECTION******/

void update_sprite(struct sprite * s)
{
	if (s == NULL)
		return;

	s->anim_timer++;
	if (s->anim_timer >= s->timer_reset) {
		s->anim_timer = 0;
		advance_state(s);
	}
}

void render_sprite(struct sprite * s)
{
	int i;
	int j;

	if (s == NULL)
		return;

	for (i = s->col; i < s->col + s->width; i++) {
		for (j = s->row; j < s->row + s->height; j++) {
			draw(s->frames[s->anim_state], i, j, M_GREEN);
		}
	}
}

void set_anim_params(struct sprite * s, int anim_state, int anim_timer, int timer_reset)
{
	if (s == NULL)
		return;

	s->anim_state = anim_state;
	s->anim_timer = anim_timer;
	s->timer_reset = timer_reset;
}

void set_frames(struct sprite * s, char const * frames)
{
	size_t len;
	char * new_frames;

	if (s == NULL)
		return;

	len = strlen(frames);
	new_frames = (char *) malloc(sizeof(*(s->frames) * len));
	if (new_frames == NULL)
		abort_game("malloc failed in function \'set_frames\'");
	strncpy(new_frames, frames, len);

	s->frames = new_frames;
}

static void advance_state(struct sprite * s)
{
	if (s == NULL)
		return;

	s->anim_state++;
	if (s->anim_state >= s->frames_len)
		s->anim_state = 0;
}
