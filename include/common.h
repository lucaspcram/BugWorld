#ifndef COMMON_H
#define COMMON_H

#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
 * Collection of unrelated utility functions/definitions.
 */

#define M_SAFEMALLOC(size) malloc_safe(size, __FILE__, __LINE__)
#define M_ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

extern pthread_mutex_t g_ncurses_mut;

int get_rand_int(int low_inc, int high_ex);

bool percentage_chance(double rate);

void abort_game(char const * msg, char const * file, unsigned long line);

void * malloc_safe(size_t size, char const * file, unsigned long line);

uint64_t ms2ns(uint64_t msec);

#endif
