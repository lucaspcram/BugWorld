#ifndef PERLIN_H
#define PERLIN_H

#include <stdbool.h>

/*
 * A 2D Perlin noise implementation.
 * Hopefully this is correct (or close enough).
 */

void init_perlin(bool shuffle);

double noise(double x, double y, double z);

#endif
