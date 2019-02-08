#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"

int assertTrue(int x, int y) { return x == y; }
#define A_TRUE printf("----- PASSED TEST -----\n");
#define A_FALSE printf("----- FAILED TEST -----\n");
	


int main(){
	struct gameState G;
	int ans;
	int i;
	int player = 0;
	int numPlayers = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	initializeGame(numPlayers,k,5,&G);
	
	G.hand[0][0] = great_hall;
	for (i = 0; i < 5; ++i){
		printf("hand: %d\n",G.hand[player][i]);
	}
	printf("%d\n",G.whoseTurn);
	playCard(0,0,0,0,&G);
	printf("%d\n",G.whoseTurn);
	playCard(1,0,0,0,&G);
	printf("%d\n",G.whoseTurn);
}

	
