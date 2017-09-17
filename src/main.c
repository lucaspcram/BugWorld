
#include "game.h"
#include "view.h"

#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void display_help(void);
void display_version(void);
void sig_handler(int sig);

static char const * G_VERSION_TEXT =
     "Bugworld v0.1, 2017\nLicense MIT\nWritten by Lucas Cram";

int main(int argc, char * argv[])
{
	int c;
	int option_index;
	struct sigaction sa;
	struct option long_options[] =
	{
		{"backend", required_argument, 0, 'b'},
		{"fps", required_argument, 0, 'f'},
		{"help", no_argument, 0, 'h'},
		{"version", no_argument, 0, 'v'}
	};

	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);

	// DEFAULTS
	g_backend = E_PTHREAD;
	g_fps = M_DEFAULT_FPS;

	while(1) {
		option_index = 0;
		c = getopt_long(argc, argv, "b:f:hv", long_options, &option_index);
		if (c == -1)
			break;
		switch(c) {
			case 0:
				break;

			case 'b':
				if (strcmp(optarg, "pthread") == 0)
					g_backend = E_PTHREAD;
				else if (strcmp(optarg, "sigalrm") == 0)
					g_backend = E_SIGALRM;
				else {
					fprintf(stderr, "Invalid argument \'%s\' to option \'--backend\'\n", optarg);
					fprintf(stderr, "Try \'bugworld --help\' for info.\n");
					return 1;
				}
				break;

			case 'f':
				g_fps = atoi(optarg);
				if (g_fps == 0) {
					fprintf(stderr, "Invalid argument \'%s\' to option \'--fps\'\n", optarg);
					fprintf(stderr, "Try \'bugworld --help\' for info.\n");
					return 1;
				}
				break;

			case 'h':
				display_help();
				return 0;

			case 'v':
				display_version();
				return 0;

			default:
				return 1;
		}
	}

	init_game();
	return 0;
}

void display_help(void)
{
	printf("Usage: bugworld [OPTION]...\n");
	printf("An animated ncurses based puzzle game.\n\n");
	printf("The following options can be used.\n");
	printf("  -b, --backend=BACKEND   Specify the concurrency backend to use.\n");
	printf("                          BACKEND can be \'sigalrm\' or \'pthread\'. Different\n");
	printf("                          backends can cause flicker on different terminals, due to\n");
	printf("                          the thread-unsafe nature of the ncurses library.\n");
	printf("                          Use whichever works best. Defaults to \'pthread\'.\n\n");
	printf("  -f, --fps=FPS           Specify the FPS at which to run. Set to lower value\n");
	printf("                          if excessive flickering occurs. Defaults to 60.\n\n");
	printf("  -h, --help              Display this help message and exit.\n\n");
	printf("  -v, --version           Display the version and exit.\n");
}

void display_version(void)
{
	printf("%s\n", G_VERSION_TEXT);
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
