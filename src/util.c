#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ncurses.h>

#define M_EPSILON (0.00000001)

char const * G_FATAL_MSG = "BugWorld FATAL ERROR\n";

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
void abort_game(char const * msg)
{
	nocbreak();
	endwin();
	fprintf(stderr, "BugWorld FATAL: %s\n", msg);
	fprintf(stderr, "Aborting.\n");
	exit(1);
}
