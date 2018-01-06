#include "common.h"
#include "view.h"

#include <execinfo.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define M_EPSILON (0.00000001)
#define M_MAX_FRAMES (128)

pthread_mutex_t g_ncurses_mut;

/*
 * This function is plagued with various *potential* problems.
 * 1) Passing invalid parameters silently returns 0.
 * 2) Uses a naive random algorithm that biases the output
 *    see http://www.azillionmonkeys.com/qed/random.html
 * Some unit testing shows that this may not be an issue for the
 * use cases present in this game.
 */
int get_rand_int(int low_incl, int high_excl)
{
	int r;
	int range;

	if (low_incl > high_excl)
		return 0;

	r = rand();
	range = high_excl - low_incl;

	return (r % range) + low_incl;
}

/*
 * Returns 'true' with probability given by the
 * parameter 'rate'. Automatically returns false
 * if the rate is less than M_EPSILON. This is to
 * support the use case percentage_chance(0.0) where
 * the 0.0 argument is not quite 0 due to roundoff errors.
 */
bool percentage_chance(double rate)
{
	double r;

	if (fabs(rate) < M_EPSILON)
		return false;

	r = (double) rand() / (double) RAND_MAX;

	return r <= rate;
}

/*
 * Aborts the game, closes ncurses, and prints an abort message to stderr.
 * Note that this function does not free any heap-allocated objects.
 */
void abort_game(char const * msg, char const * file, unsigned long line)
{
	/*
	void * frames[M_MAX_FRAMES];
	char ** trace;
	size_t size;
	size_t i;
	*/

	destroy_graphics();

	/*
	print a stack trace
	based on sample from
	https://www.gnu.org/software/libc/manual/html_node/Backtraces.html
	FIXME periodically breaks ncurses cleanup for some reason
	*/
	
	/*
	size = backtrace(frames, M_MAX_FRAMES);
	trace = backtrace_symbols(frames, size);
	for (i = 0; i < size; i++)
		fprintf (stderr, "%s\n", trace[i]);
	free(trace);
	*/

	fprintf(stderr, "BugWorld FATAL: %s\n", msg);
	fprintf(stderr, "Error from %s on line %lu\n", file, line);
	fprintf(stderr, "Aborting.\n");
	exit(1);
}

/*
 * Special wrapper for the stdlib malloc. Aborts with a
 * message if malloc fails. Should be called using
 * M_SAFEMALLOC macro.
 */
void * malloc_safe(size_t size, char const * file, unsigned long line)
{
	void * ptr;

	ptr = malloc(size);
	if (ptr == NULL) {
		abort_game("malloc call failed", file, line);
	}
	return ptr;
}

/*
 * Takes a millisecond value and converts
 * it to the closest possible nanosecond value.
 */
uint64_t ms2ns(uint64_t msec)
{
	uint64_t const ns = msec * 1000000;
	return ns;
}

/*
 * Compute the dot product of two vec2d.
 */
double vec2d_dot(struct vec2d const * v1, struct vec2d const * v2)
{
	if (v1 == NULL || v2 == NULL)
		return 0;

	return v1->x * v2->x + v1->y * v2->y;
}

/*
 * Compute the magnitude of a vec2d.
 */
double vec2d_magn(struct vec2d const * v)
{
	double xsq, ysq;

	if (v == NULL)
		return 0;

	xsq = v->x * v->x;
	ysq = v->y * v->y;

	return sqrt(xsq + ysq);
}

