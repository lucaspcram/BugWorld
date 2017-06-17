#include "view.h"

#include <stdio.h>
#include <ncurses.h>

#define M_RED (1)
#define M_GREEN (2)
#define M_YELLOW (3)
#define M_CYAN (4)
#define M_MAGENTA (5)

static WINDOW * g_emptywin;
static WINDOW * g_masterwin;

static void init_emptywin();
static void init_masterwin();

static void init_emptywin()
{
	g_emptywin = newpad(M_SCRHEIGHT, M_SCRWIDTH);
	wclear(g_emptywin);
}

static void init_masterwin()
{
	g_emptywin = newwin(M_SCRHEIGHT, M_SCRWIDTH, 0, 0);
	wclear(g_masterwin);
	mvwin(g_masterwin, 0, 0);
}

void init_graphics()
{
	initscr();
	cbreak();
	noecho();
	start_color();

	init_pair(M_RED, COLOR_RED, COLOR_BLACK);
	init_pair(M_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(M_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(M_CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(M_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);

	init_emptywin();
	init_masterwin();
}

void destroy_graphics()
{
	nocbreak();
	endwin();
}