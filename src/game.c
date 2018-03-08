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

#define M_USEC_PER_SEC (1000000)
#define M_NSEC_PER_SEC (1000000000)
#define M_NSEC_PER_USEC (1000)

int g_fps;
time_t g_seed;

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

    init_graphics();
    init_state_manager();
    srand(g_seed);

    pthread_mutex_init(&g_ncurses_mut, NULL);
    err = pthread_create(&thread, NULL, tick, NULL);
    if (err)
        abort_game("pthread_create failed", __FILE__, __LINE__);

    input_loop();

    pthread_join(thread, NULL);

    destroy_state_manager();
    destroy_graphics();
}

void input_loop(void)
{
    int ch;

    while (!exit_flag) {
        /*
        The entire input sequence must be marked as
        a critical section since it can modify game
        state currently being accessed by the tick_render
        thread
        */
        pthread_mutex_lock(&g_ncurses_mut);
        timeout(0);
        ch = getch();
        if (ch == ERR) {
            pthread_mutex_unlock(&g_ncurses_mut);
            continue;
        }

        /* send input to the state manager */
        handle_input(ch);

        pthread_mutex_unlock(&g_ncurses_mut);
    }
}

void * tick(void * arg)
{
    struct timespec req, rem;
    struct timespec start, end, cur;
    uint64_t frame_time;
    uint64_t nsec_elapsed;
    uint64_t const nsec_perframe = M_NSEC_PER_SEC / g_fps;

    /*
    NOTE: Two calculations are happening in this loop.
    1) the elapsed time since the previous tick_render cycle,
       which is passed into the next tick_render as frame_time
    2) the time spent in just the tick_render call, so the thread
       can sleep for an appropriate amount of time to hit g_fps
    */

    clock_gettime(CLOCK_MONOTONIC, &cur);
    while (1) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        if (start.tv_sec > cur.tv_sec) {
            frame_time = (M_NSEC_PER_SEC * start.tv_sec + start.tv_nsec)
                         - (M_NSEC_PER_SEC * cur.tv_sec + cur.tv_nsec);
        } else {
            frame_time = start.tv_nsec - cur.tv_nsec;
        }
        cur.tv_sec = start.tv_sec;
        cur.tv_nsec = start.tv_nsec;

        pthread_mutex_lock(&g_ncurses_mut);
        tick_render(frame_time);
        pthread_mutex_unlock(&g_ncurses_mut);

        clock_gettime(CLOCK_MONOTONIC, &end);

        /*
        NOTE: all of this code relies on the elapsed time
        being < the value of nsec_perframe, this should be
        the case on any non-potato system
        */
        nsec_elapsed = end.tv_nsec - start.tv_nsec;
        req.tv_sec = 0;
        req.tv_nsec = nsec_perframe - nsec_elapsed;
        if (req.tv_nsec < 0)
            req.tv_nsec = 0;
        nanosleep(&req, &rem);
        if (exit_flag)
            break;
    }

    return NULL;
}
