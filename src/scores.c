#include "common.h"
#include "scores.h"

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static char const * G_SCOREFILE = ".bugworldscore";

/*
 * Attempts to create the scorefile in the user's home directory.
 * Returns the path to the file on success.
 */
char * create_scorefile(void)
{
    char * homedir;
    char * scorepath;
    size_t len_homedir;
    size_t len_scorefile;
    size_t len_total;
    FILE * score_file;

    /* 
    gets the user's home directory by trying GETENV
    and then checking the passwd file if that fails
    */
    homedir = getenv("home");
    if (homedir == NULL)
        homedir = getpwuid(getuid())->pw_dir;
    
    len_homedir = strlen(homedir);
    len_scorefile = strlen(G_SCOREFILE);
    /* the +1 is to account for extra '/' between homedir and scorefile */
    len_total = len_homedir + 1 + len_scorefile;

    scorepath = M_SAFEMALLOC(sizeof(*scorepath) * (len_total + 1));
    strcpy(scorepath, homedir);
    strcat(scorepath, "/");
    strcat(scorepath, G_SCOREFILE);

    /*
    NOTE access() is vulnerable to race condition if the file
    is created between calling access() and fopen()-ing the file
    */
    if (access(scorepath, F_OK) == -1) {
        score_file = fopen(scorepath, "w");
        fclose(score_file);
    }

    return scorepath;
}

/*
 * Takes a NULL terminated array of score struct pointers. Writes
 * the struct data sequentially to the scorefile.
 */
void write_scorefile(struct score ** scores, char * scorepath)
{
    size_t len;
    struct score ** tmp;
    FILE * file;

    file = fopen(scorepath, "wb");
    if (file == NULL)
        return;

    len = len_scorelist(scores);
    tmp = scores;

    /* first byte of file stores array len */
    fwrite(&len, sizeof(size_t), 1, file);
    
    while (*tmp != NULL) {
        fwrite(*tmp, sizeof(struct score), 1, file);
        tmp++;
    }

    fclose(file);
}

/*
 * Reads the scorefile into a NULL terminated array of score
 * struct pointers.
 */
struct score ** read_scorefile(char * scorepath)
{
    int i;
    size_t len;
    struct score ** scores;
    struct score ** tmp;
    FILE * file;

    file = fopen(scorepath, "rb");
    if (file == NULL)
        return NULL;

    /* first byte of file stores array len */
    fread(&len, sizeof(size_t), 1, file);
    scores = M_SAFEMALLOC(sizeof(*scores) * (len + 1));

    tmp = scores;
    i = 0;
    while (i < len) {
        *tmp = M_SAFEMALLOC(sizeof(**tmp));
        fread(*tmp, sizeof(struct score), 1, file);
        tmp++;
        i++;
    }

    *tmp = NULL;
    fclose(file);
    
    return scores;
}

void free_scorelist(struct score ** scores)
{
    struct score ** tmp;

    if (scores == NULL)
        return;

    tmp = scores;

    while (*tmp != NULL) {
        free(*tmp);
        tmp++;
    }

    free(scores);
}

size_t len_scorelist(struct score ** scores)
{
    size_t len;
    struct score ** tmp;

    len = 0;
    if (scores == NULL)
        return len;

    tmp = scores;

    while (*tmp != NULL) {
        len++;
        tmp++;
    }

    return len;
}

/*
 * Comparator function for sorting scores. Uses 'levels_cleared'
 * field as the key.
 */
int compare_score(void const * a, void const * b)
{
    struct score * score_a;
    struct score * score_b;

    score_a = *(struct score **) a;
    score_b = *(struct score **) b;

    return score_b->levels_cleared - score_a->levels_cleared;
}

/*
 * Sorts the provided array of score struct pointers.
 */
void sort_scores(struct score ** scores)
{
    size_t len;

    len = len_scorelist(scores);
    qsort((void *) scores, len, sizeof(struct score *), compare_score);
}
