#ifndef PERLIN_H
#define PERLIN_H

#include <stdbool.h>

/*
 * A 2D Perlin noise implementation.
 */

void init_perlin(bool shuffle);

double p_noise(double x, double y);

#endif
