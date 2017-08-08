#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

/*
 * Collection of unrelated utility functions/definitions.
 */

extern char const * G_FATAL_MSG;

int get_rand_int(int low_inc, int high_ex);

bool percentage_chance(double rate);

void abort_game(char const * msg);

#endif
