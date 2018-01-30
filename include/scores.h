#ifndef SCORES_H
#define SCORES_H

/*
 * Definitions and functions for the scores/stats tracking system.
 */

#include <sys/types.h>

struct score {
    int score;
    int levels_cleared;
};

char * create_scorefile(void);
void write_scorefile(struct score ** scores, char * scorepath);
struct score ** read_scorefile(char * scorepath);
struct score ** add_score(struct score ** scores, struct score * newscore);
void free_scorelist(struct score ** scores);
size_t len_scorelist(struct score ** scores);
int compare_score(void const * a, void const * b);
void sort_scores(struct score ** scores);

#endif
