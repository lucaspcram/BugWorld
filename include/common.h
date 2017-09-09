#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Collection of unrelated utility functions/definitions.
 */

#define M_SAFEMALLOC(size) malloc_safe(size, __FILE__, __LINE__)

extern char const * G_FATAL_MSG;

int get_rand_int(int low_inc, int high_ex);

bool percentage_chance(double rate);

void abort_game(char const * msg, char const * file, unsigned long line);

void * malloc_safe(size_t size, char const * file, unsigned long line);

#endif
