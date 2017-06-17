#ifndef VIEW_H
#define VIEW_H

/*
 * Contains all the code to handle ncurses related tasks.
 * Things like initializing the screen, closing the screen, etc.
 */

// NOTE Runs in a standard 24x80 terminal
// TODO do these belong here or in the C file?
#define M_SCRWIDTH (80) // term columns
#define M_SCRHEIGHT (24) // term rows

void init_graphics(void);
void destroy_graphics(void);

#endif