#ifndef SCORES_H
#define SCORES_H

#define MAX_LEN_NAME 256

#include <sys/types.h>

/*
 * Definitions and functions for the scores/stats tracking system.
 */

struct score {
	char name[MAX_LEN_NAME];
	int levels_cleared;
	int turns_elapsed;
	int decoys_used;
};

char * create_scorefile(void);
void write_scorefile(struct score ** scores, char * scorepath);
struct score ** read_scorefile(char * scorepath);
void free_scorelist(struct score ** scores);
size_t len_scorelist(struct score ** scores);
int compare_score(void const * a, void const * b);
void sort_scores(struct score ** scores);

#endif
