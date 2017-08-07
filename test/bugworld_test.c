#include "util.h"
#include "scores.h"
#include "sprite.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define M_MAX_TRIALS (10000000)
#define M_MAX_BIN (10)
#define M_RATE (0.5)

void test_rand();
void test_score_io();
void test_sprites();

int main(int argc, char * argv[])
{
	printf("BugWorld Unit Tests\n");
	
	// Test the robustness of the random number generator.
	test_rand();

	// Test the highscore file IO functionality
	test_score_io();

	// Test the sprites
	test_sprites();

	return 0;
}

void test_rand()
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
}

void test_score_io()
{
	struct score score1;
	struct score score2;
	struct score score3;
	struct score ** scores;
	struct score ** tmp;
	char * scorepath;
	
	printf("\n### SCOREFILE IO TEST ###\n");

	memset(score1.name, 0, sizeof(score1.name));
	strcpy(score1.name, "Beetle");
	score1.levels_cleared = 3;
	score1.turns_elapsed = 10;
	score1.decoys_used = 2;

	memset(score2.name, 0, sizeof(score1.name));
	strcpy(score2.name, "AnotherBeetle");
	score2.levels_cleared = 1;
	score2.turns_elapsed = 1;
	score2.decoys_used = 1;

	memset(score3.name, 0, sizeof(score3.name));
	strcpy(score3.name, "Testing");
	score3.levels_cleared = 100;
	score3.turns_elapsed = 2;
	score3.decoys_used = 2;

	scores = (struct score **) malloc(sizeof(*scores) * 4);
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

	tmp = scores;
	while (*tmp != NULL) {
		printf("---SCORE STRUCT---\n");
		printf("%s\n%d\n%d\n%d\n\n", (*tmp)->name, 
			(*tmp)->levels_cleared, (*tmp)->turns_elapsed, (*tmp)->decoys_used);
		tmp++;
	}

	printf("Sorting the array...\n");
	sort_scores(scores);

	tmp = scores;
	while (*tmp != NULL) {
		printf("---SCORE STRUCT---\n");
		printf("%s\n%d\n%d\n%d\n\n", (*tmp)->name, 
			(*tmp)->levels_cleared, (*tmp)->turns_elapsed, (*tmp)->decoys_used);
		tmp++;
	}

	free_scorelist(scores); 
	free(scorepath);
}

void test_sprites()
{
	struct sprite * sprite1;

	printf("\n### SPRITE LIFECYCLE TEST ###\n");

	sprite1 = create_sprite(0, 0, 0, 0);
	set_frames(sprite1, "\\|/|");
	destroy_sprite(sprite1);

	printf("Sprite lifecycle OK\n");
}
