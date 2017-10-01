#ifndef VIEW_H
#define VIEW_H

/*
 * Contains all the code to handle ncurses related tasks.
 * Things like initializing the screen, closing the screen, etc.
 */

/* NOTE Runs in a standard 24x80 terminal */
#define M_SCRWIDTH (80)
#define M_SCRHEIGHT (24)

#define M_RED (1)
#define M_GREEN (2)
#define M_YELLOW (3)
#define M_CYAN (4)
#define M_MAGENTA (5)
#define M_BLACK (6)
#define M_BLUE (7)
#define M_WHITE (8)

void init_graphics(void);
void destroy_graphics(void);
void draw(char ch, int col, int row, int color);
void draw_str(char const * str, int col, int row, int color);
void refresh_view(void);
void clear_view(void);

#endif
