
#include "common.h"
#include "gameobj/sprite.h"
#include "gameobj/player.h"
#include "perlin.h"
#include "scores.h"
#include "world/world.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define M_MAX_TRIALS (10000000)
#define M_MAX_BIN (10)
#define M_RATE (0.5)

#define M_TRY_TEST(function) \
do {                         \
if(function()) return 1;     \
} while(0)

int test_rand();
int test_score_io();
int test_gameobj();
int test_perlin();

int main(int argc, char * argv[])
{
    printf("BugWorld Unit Tests\n");
    
    /* Test the robustness of the random number generator */
    /*M_TRY_TEST(test_rand);*/

    /* Test the highscore file IO functionality */
    M_TRY_TEST(test_score_io);

    /* Test gameobj code */
    M_TRY_TEST(test_gameobj);

    /* Test Perlin noise impl */
    /*M_TRY_TEST(test_perlin);*/

    return 0;
}

int test_rand()
{
    int i;
    int num;
    int counter;
    double frac;
    int results[M_MAX_BIN];

    printf("\n### RANDOM UTILITY UNIT TEST ###\n");

    srand(time(NULL));

    printf("\nTesting get_rand_int() with %d bins\n", M_MAX_BIN);
    for (i = 0; i < M_MAX_BIN; i++)
        results[i] = 0;
    
    for (i = 0; i < M_MAX_TRIALS; i++) {
        num = get_rand_int(0, M_MAX_BIN);
        results[num]++;
    }
    for (i = 0; i < M_MAX_BIN; i++) {
        frac = (double) results[i] / M_MAX_TRIALS;
        printf("Bin %d: %lf\n", i, frac);
    }
    printf("Expected fraction: %lf\n", 1.0 / M_MAX_BIN);


    printf("\nTesting percentage_chance() with rate %lf\n", M_RATE);
    counter = 0;
    for (i = 0; i < M_MAX_TRIALS; i++) {
        if (percentage_chance(M_RATE))
            counter++;
    }
    printf("Percentage chance fraction: %lf\n", (double) counter / M_MAX_TRIALS);
    printf("Expected fraction: %lf\n", (double) M_RATE);

    return 0;
}

int test_score_io()
{
    struct score score1;
    struct score score2;
    struct score score3;
    struct score * new_score;
    struct score ** scores;
    struct score ** tmp;
    char * scorepath;
    
    printf("\n### SCOREFILE IO TEST ###\n");

    score1.score = 12;
    score1.levels_cleared = 3;
    score1.seed = 1;

    score2.score = 490;
    score2.levels_cleared = 1;
    score2.seed = 112312;

    score3.score = 12;
    score3.levels_cleared = 100;
    score3.seed = 10;

    new_score = M_SAFEMALLOC(sizeof(*new_score));
    new_score->score = 5000;
    new_score->levels_cleared = 100;
    new_score->seed = 123;

    scores = M_SAFEMALLOC(sizeof(*scores) * 4);
    scores[0] = &score1;
    scores[1] = &score2;
    scores[2] = &score3;
    scores[3] = NULL;


    scorepath = create_scorefile();
    printf("Writing struct data to %s\n\n", scorepath);
    write_scorefile(scores, scorepath);
    free(scores);

    printf("Reading back struct data...\n");
    scores = read_scorefile(scorepath);

    printf("Adding a score to the end...\n");
    scores = add_score(scores, new_score);

    tmp = scores;
    while (*tmp != NULL) {
        printf("---SCORE STRUCT---\n");
        printf("%d\n%d\n%ld\n\n", (*tmp)->score, (*tmp)->levels_cleared, (*tmp)->seed);
        tmp++;
    }

    printf("Sorting the array...\n");
    sort_scores(scores);

    tmp = scores;
    while (*tmp != NULL) {
        printf("---SCORE STRUCT---\n");
        printf("%d\n%d\n%ld\n\n", (*tmp)->score, (*tmp)->levels_cleared, (*tmp)->seed);
        tmp++;
    }

    free_scorelist(scores); 
    free(scorepath);

    return 0;
}

int test_gameobj()
{
    struct world * w;

    printf("\n### GAMEOBJ LIFECYCLE TEST ###\n");

    printf("Creating world...\n");
    w = create_world();
    printf("Destroying world...\n");
    destroy_world(w);

    return 0;
}

int test_perlin()
{
    int i, j;
    double d, x, y;

    printf("\n### PERLIN NOISE TEST ###\n");
    init_perlin(false);

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            x = ((double) i) + 0.5;
            y = ((double) j) + 0.5;
            d = p_noise(x, y);
            printf("noise: %lf\n", d);
        }
    }

    return 0;
}
