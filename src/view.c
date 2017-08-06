#include "view.h"

#include <stdio.h>
#include <ncurses.h>

void init_graphics()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	start_color();

	init_pair(M_RED, COLOR_RED, COLOR_BLACK);
	init_pair(M_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(M_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(M_CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(M_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(M_BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair(M_BLUE, COLOR_BLUE, COLOR_BLACK);
}

void destroy_graphics()
{
	nocbreak();
	endwin();
}

void draw(char ch, int col, int row, int color)
{
	char buf[2];

	if (col >= M_SCRWIDTH || col < 0 || row >= M_SCRHEIGHT || row < 0)
		return;

	sprintf(buf, "%c", ch);
	attron(COLOR_PAIR(color));
	mvprintw(row, col, buf);
	attroff(COLOR_PAIR(color));
}

void draw_str(char const * str, int col, int row, int color)
{
	if (col >= M_SCRWIDTH || col < 0 || row >= M_SCRHEIGHT || row < 0)
		return;

	attron(COLOR_PAIR(color));
	mvprintw(row, col, str);
	attroff(COLOR_PAIR(color));
}

void refresh_view()
{
	refresh();
}

void clear_view()
{
	clear();
}
