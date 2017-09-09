#include "view.h"
#include "game.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <signal.h>

void display_help(void);
void display_version(void);
void sigterm_handler(int sig);

char const * VERSION_TEXT =
     "Bugworld v0.1, 2017\nLicense MIT\nWritten by Lucas Cram";

int main(int argc, char * argv[])
{
	int c;

	signal(SIGTERM, sigterm_handler);

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

void sigterm_handler(int sig)
{
	destroy_graphics();
}
