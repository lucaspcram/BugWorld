
#include "game.h"
#include "view.h"

#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void display_help(char * progname);
void display_version(void);
void sig_handler(int sig);

static char const * G_VERSION_TEXT =
     "Bugworld v1.0, 2017\nLicensed under the MIT License\nWritten by Lucas Cram";

int main(int argc, char * argv[])
{
    int c;
    int option_index;
    struct sigaction sa;
    struct option long_options[] =
    {
        {"fps", required_argument, 0, 'f'},
        {"help", no_argument, 0, 'h'},
        {"seed", required_argument, 0, 's'},
        {"version", no_argument, 0, 'v'},
        {NULL, 0, NULL, 0}
    };

    sa.sa_handler = &sig_handler;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);

    /* DEFAULTS */
    g_fps = M_DEFAULT_FPS;
    g_seed = time(NULL);

    while(1) {
        option_index = 0;
        c = getopt_long(argc, argv, "f:hs:v", long_options, &option_index);
        if (c == -1)
            break;
        switch(c) {
            case 0:
            break;

            case 'f':
            g_fps = atoi(optarg);
            if (g_fps < 5 || g_fps > 60) {
                fprintf(stderr, "Invalid argument \'%s\' to option \'--fps\'\n", optarg);
                fprintf(stderr, "Try \'bugworld --help\' for info.\n");
                return 1;
            }
            break;

            case 'h':
            display_help(argv[0]);
            return 0;

            case 's':
            g_seed = atoi(optarg);
            if (g_seed < 1 || g_seed > 999999999) {
                fprintf(stderr, "Invalid argument \'%s\' to option \'--seed\'\n", optarg);
                fprintf(stderr, "Try \'bugworld --help\' for info.\n");
                return 1;
            }
            break;

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

void display_help(char * progname)
{
    printf("Usage: %s [OPTION ...]\n", progname);
    printf("An animated ncurses based puzzle game.\n\n");
    printf("The following options can be used.\n");
    printf("  -f, --fps=FPS           Specify the FPS at which to run. Try setting to different\n");
    printf("                          values if excessive flickering occurs. Defaults to 10.\n");
    printf("                          Valid settings range is [5, 60].\n\n");
    printf("  -h, --help              Display this help message and exit.\n\n");
    printf("  -s, --seed=SEED         Specify a seed for the world generator. The provided seed\n");
    printf("                          must be in range [1, 999999999]. If no seed is given, defaults\n");
    printf("                          to the current system time.\n\n");
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
        /* fallthru to SIGTERM */

        case SIGTERM:
        destroy_graphics();
        break;

        default:
        return;
    }
    exit(0);
}
