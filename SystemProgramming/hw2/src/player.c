#include <stdio.h>
#include "my_header.h"

int main(int argc, char *argv[]) {
	int winner_id, ok;
	int player_id = (int)strtol(argv[1], NULL, 10);
	/*
	for (int i = 0; i < NUM_ROUNDS; ++i) {
		
		if (i != 0) {
			scanf("%d\n", &winner_id);
		}
		
		printf("%d %d\n", player_id, player_id * 10);
		fflush(stdout);
	}
	*/
	printf("%d %d\n", player_id, player_id * 10);
	fflush(stdout);
	exit(0);
}