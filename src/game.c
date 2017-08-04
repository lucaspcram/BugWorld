#include "game.h"
#include "view.h"
#include "state_manager.h"

#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <ncurses.h>

void init_game(void)
{
	init_graphics();
	init_state_manager();

	set_sigalarm();
	input_loop();

	destroy_state_manager();
	destroy_graphics();
}

void input_loop(void)
{
	char ch;

	while (!exit_flag) {
		ch = getch();
		statemgr_update_input(ch);
	}
}

void tick(int sig)
{
	statemgr_update_render();
}

/*
 * Sets a SIGALRM to call the 'tick()' function
 * approx. FPS times per second
 */
void set_sigalarm()
{
	struct itimerval timer;
	struct sigaction action;
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 1000000 / FPS;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 1000000 / FPS;
	setitimer(ITIMER_REAL, &timer, NULL);
	
	action.sa_handler = &tick;
	action.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &action, NULL);
}
