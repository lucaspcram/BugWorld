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

void render_sprite(struct sprite * s, int color)
{
	int i;
	int j;

	if (s == NULL)
		return;

	for (i = 0; i < s->height; i++) {
		for (j = 0; j < s->width; j++) {
			draw(s->frames[s->anim_state][(i * s->width) + j], j + s->col, i + s->row, color);
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

/*
 * Each element in the 'frames' string array is a 1D representation
 * of 1 frame of a 2D sprite.
 *
 * For example, the sprite animation:
 *
 *     a b a    b a b    a b a
 *     c d c -> d c d -> c d c
 *     e f e    f e f    e f e
 *
 * would be encoded as:
 *
 *    char const * MY_SPRITE[] = 
 *    {
 *    "abacdcefe",
 *    "babdcdfef",
 *    "abacdcefe"
 *    };
 *
 *
 */
void set_frames(struct sprite * s, char const ** frames, int frames_len)
{
	size_t len;
	int i;
	char ** new_frames;

	if (s == NULL)
		return;

	new_frames = (char **) malloc(sizeof(*new_frames) * frames_len);
	if (new_frames == NULL)
		abort_game("malloc failed in function \'set_frames\'");

	for (i = 0; i < frames_len; i++) {
		len = strlen(frames[i]);
		new_frames[i] = (char *) malloc(sizeof(*new_frames[i]) * len);

		if (new_frames[i] == NULL)
			abort_game("malloc failed in function \'set_frames\'");

		strncpy(new_frames[i], frames[i], len);
	}

	s->frames = new_frames;
	s->frames_len = frames_len;
}

static void advance_state(struct sprite * s)
{
	if (s == NULL)
		return;

	s->anim_state++;
	if (s->anim_state >= s->frames_len)
		s->anim_state = 0;
}
