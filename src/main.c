#include "view.h"
#include "game.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void display_help();

int main(int argc, char * argv[])
{
	int c;

	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c) {
			case 'h':
				display_help();
			break;
			
			case '?':
				fprintf(stderr, 
					"Unknown option -%c. Use \'-h\' for help.\n", optopt);
				return 1;
			
			default:
				exit(1);
		}
	}
	init_game();
	return 0;
}

void display_help()
{
	printf("TODO: Bugworld help screen.\n");
}
