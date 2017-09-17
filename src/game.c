#include "game.h"

#include "common.h"
#include "state_manager.h"
#include "view.h"

#include <ncurses.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define U_SEC_PER_SEC (1000000)
#define M_NSEC_PER_SEC (1000000000)

enum concurrency_backend g_backend;
int g_fps;

/*
 * Combines POSIX threads with ncurses to achieve animated graphical
 * effects.
 *
 * main thread: runs an input loop that calls getch() and updates
 *              game logic accordingly
 * tick thread: runs ~M_FPS times per second, updating animations and
 *              drawing the game
 *
 * Note that ncurses is not technically thread-safe, but the thread
 * task delegation is handled such that it *should* work.
 */
void init_game(void)
{
	pthread_t thread;
	int err;

	srand(time(NULL));
	init_graphics();
	init_state_manager();

	if (g_backend == E_PTHREAD) {
		pthread_mutex_init(&g_ncurses_mut, NULL);
		err = pthread_create(&thread, NULL, tick_pthread, NULL);
		if (err)
			abort_game("pthread_create failed", __FILE__, __LINE__);
		input_loop_pthread();
	} else if (g_backend == E_SIGALRM) {
		set_sigalrm();
		input_loop_sigalrm();
	} else {
		// this should not happen
		abort_game("invalid backend setting", __FILE__, __LINE__);
	}

	destroy_state_manager();
	destroy_graphics();
}

void input_loop_pthread(void)
{
	int ch;

	while (!exit_flag) {
		pthread_mutex_lock(&g_ncurses_mut);
		timeout(0);
		ch = getch();
		if (ch == ERR) {
			pthread_mutex_unlock(&g_ncurses_mut);
			continue;
		}
		pthread_mutex_unlock(&g_ncurses_mut);

		// send input to the state manager
		handle_input(ch);
	}
}

void input_loop_sigalrm(void)
{
	int ch;

	while (!exit_flag) {
		ch = getch();

		// send input to the state manager
		handle_input(ch);
	}
}

void * tick_pthread(void * arg)
{
	struct timespec req, rem;
	struct timespec start, end;
	uint64_t nsec_elapsed;
	uint64_t const nsec_perframe = M_NSEC_PER_SEC / g_fps;

	while (1) {
		pthread_mutex_lock(&g_ncurses_mut);
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		tick_render();
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		pthread_mutex_unlock(&g_ncurses_mut);

		// NOTE: all of this code relies on the elapsed time
		// being < the value of nsec_perframe, this should be
		// the case on any non-potato system
		nsec_elapsed = end.tv_nsec - start.tv_nsec;
		req.tv_sec = 0;
		req.tv_nsec = nsec_perframe - nsec_elapsed;
		if (req.tv_nsec < 0)
			req.tv_nsec = 0;
		nanosleep(&req, &rem);
	}
}

void tick_sigalrm(int sig)
{
	tick_render();
}

void set_sigalrm(void)
{
	struct itimerval timer;
	struct sigaction action;
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = U_SEC_PER_SEC / g_fps;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = U_SEC_PER_SEC / g_fps;
	setitimer(ITIMER_REAL, &timer, NULL);

	action.sa_handler = &tick_sigalrm;
	action.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &action, NULL);
}
