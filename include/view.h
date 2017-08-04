#ifndef VIEW_H
#define VIEW_H

/*
 * Contains all the code to handle ncurses related tasks.
 * Things like initializing the screen, closing the screen, etc.
 */

#define M_RED (1)
#define M_GREEN (2)
#define M_YELLOW (3)
#define M_CYAN (4)
#define M_MAGENTA (5)
#define M_BLACK (6)

void init_graphics(void);
void destroy_graphics(void);
void draw(char ch, int col, int row, int color);
void draw_str(char const * str, int col, int row, int color);
void refresh_view();
void clear_view();

#endif
