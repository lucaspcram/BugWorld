
#include "game.h"
#include "view.h"

#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void display_help(void);
void display_version(void);
void sig_handler(int sig);

char const * VERSION_TEXT =
     "Bugworld v0.1, 2017\nLicense MIT\nWritten by Lucas Cram";

int main(int argc, char * argv[])
{
	int c;
	struct sigaction sa;

	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);

	while ((c = getopt(argc, argv, "hv")) != -1) {
		switch (c) {
			case 'h':
				display_help();
				exit(0);
			break;

			case 'v':
				display_version();
				exit(0);
			break;

			case '?':
				fprintf(stderr, 
					"Unknown option -%c. Use \'-h\' for help.\n", optopt);
				exit(1);
			break;

			default:
				fprintf(stderr, "Option error. Use \'-h\' for help.\n");
				exit(1);
		}
	}
	g_backend = E_PTHREAD;
	init_game();
	return 0;
}

void display_help(void)
{
	printf("TODO: Bugworld help screen.\n");
}

void display_version(void)
{
	printf("%s\n", VERSION_TEXT);
}

void sig_handler(int sig)
{
	switch(sig) {
		case SIGINT:
			// fallthru to SIGTERM
		case SIGTERM:
			destroy_graphics();
			break;
		default:
			return;
	}
	exit(0);
}
