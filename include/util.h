#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

/*
 * Collection of unrelated utility functions/definitions.
 */

/* Macro definitions for ncurses keys */
#define M_ENTER (10)
#define M_W ('w')
#define M_A ('a')
#define M_S ('s')
#define M_D ('d')

extern char const * G_FATAL_MSG;

int get_rand_int(int low_inc, int high_ex);

bool percentage_chance(double rate);

#endif