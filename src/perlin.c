#include "perlin.h"

#include "common.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct vec2d {
	double x;
	double y;
};

/*
 * Values taken from Ken Perlin's improved reference implementation.
 * http://mrl.nyu.edu/~perlin/noise/
 */
static int p_master[] = {
	151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
	8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
	35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
	134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
	55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,
	18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,
	250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
	189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,
	43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,
	97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,
	107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};
static int p[256];

// the array to hold the final permutation of p
// repeated once to prevent index-out-of-bounds during calculations
static int perm[512];

/*
 * Gradient unit vectors around the unit circle spaced 22.5deg apart.
 */
static struct vec2d grad_table[] = {
	{1, 0},
	{0.92387953, 0.38268343},
	{0.70710678, 0.70710678},
	{0.38268343, 0.92387953},
	{0, 1},
	{-0.38268343, 0.92387953},
	{-0.70710678, 0.70710678},
	{-0.92387953, 0.38268343},
	{-1, 0},
	{-0.92387953, -0.38268343},
	{-0.70710678, -0.70710678},
	{-0.38268343, -0.92387953},
	{0, -1},
	{0.92387953, -0.38268343},
	{0.70710678, -0.70710678},
	{0.38268343, -0.92387953}
};

static void shuffle_p(void);
static double fade(double t);
static double lerp(double t, double a, double b);
static void get_grad(int hash, struct vec2d * out);
static double dot(struct vec2d * v1, struct vec2d * v2);

void init_perlin(bool shuffle)
{
	size_t i;

	// reset the p array
	for (i = 0; i < M_ARRAY_SIZE(p); i++) {
		p[i] = p_master[i];
	}

	if (shuffle) {
		shuffle_p();
	}

	for (i = 0; i < M_ARRAY_SIZE(perm); i++) {
		perm[i] = p[i % M_ARRAY_SIZE(p)];
	}
}

double p_noise(double x, double y)
{
	int x_int, y_int;
	int c00, c01, c10, c11;
	double u, v;
	double p0p1, p2p3;
	double result;
	struct vec2d p, p_rel, p0, p1, p2, p3;
	struct vec2d p0d, p1d, p2d, p3d;
	struct vec2d g0, g1, g2, g3;

	// get the relative location in the unit square
	// compute the square corner vectors
	p.x = x;
	p.y = y;
	p_rel.x = p.x - floor(p.x);
	p_rel.y = p.y - floor(p.y);
	p0.x = floor(p.x);
	p0.y = floor(p.y);
	p1.x = p0.x + 1;
	p1.y = p0.y;
	p2.x = p0.x;
	p2.y = p0.y + 1;
	p3.x = p0.x + 1;
	p3.y = p0.y + 1;

	// compute the fades
	u = fade(p_rel.x);
	v = fade(p_rel.y);

	// clamp the coordinates to range [0, 255]
	// compute hashes of unit square corners
	x_int = ((int) p0.x) & 0xFF;
	y_int = ((int) p0.y) & 0xFF;
	c00 = perm[perm[x_int] + y_int];
	c01 = perm[perm[x_int] + (y_int + 1)];
	c10 = perm[perm[(x_int + 1)] + y_int];
	c11 = perm[perm[(x_int + 1)] + (y_int + 1)];

	// get the gradients at the corners
	get_grad(c00, &g0);
	get_grad(c01, &g1);
	get_grad(c10, &g2);
	get_grad(c11, &g3);

	// compute difference vectors
	p0d.x = p.x - p0.x;
	p0d.y = p.y - p0.y;
	p1d.x = p.x - p1.x;
	p1d.y = p.y - p1.y;
	p2d.x = p.x - p2.x;
	p2d.y = p.y - p2.y;
	p3d.x = p.x - p3.x;
	p3d.y = p.y - p3.y;

	// perform interpolations
	p0p1 = lerp(u, dot(&g0, &p0d), dot(&g1, &p1d));
	p2p3 = lerp(u, dot(&g2, &p2d), dot(&g3, &p3d));
	result = lerp(v, p0p1, p2p3);

	// normalize result to range [0, 1]
	return (result + 1) / 2.0;
}

// uses Fisher-Yates shuffle to randomly reorder the permutations
// assumes the rand() function has already been seeded
static void shuffle_p(void)
{
	size_t len;
	size_t i;
	size_t swap_idx;
	int tmp;

	len = M_ARRAY_SIZE(p);

	// assumes perm has size > 1
	for (i = len - 1; i > 0; i--) {
		// this rand function introduces bias
		// see note in 'common.c'
		swap_idx = get_rand_int(0, i + 1);
		tmp = p[swap_idx];
		p[swap_idx] = p[i];
		p[i] = tmp;
	}
}

static double fade(double t)
{
	double const t_cubed = t * t * t;
	return t_cubed * (t * ((t * 6) - 15) + 10);
}

// linear interpolation between 'a' and 'b'
static double lerp(double t, double a, double b)
{
	return ((1 - t) * a) + (t * b);
}

static void get_grad(int hash, struct vec2d * out)
{
	if (out == NULL) {
		return;
	}
	out->x = grad_table[hash & 0xF].x;
	out->y = grad_table[hash & 0xF].y;
}

static double dot(struct vec2d * v1, struct vec2d * v2)
{
	if (v1 == NULL || v2 == NULL)
		return 0;

	return v1->x * v2->x + v1->y * v2->y;
}
