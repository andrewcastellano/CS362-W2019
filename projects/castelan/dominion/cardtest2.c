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
	int deckCount=0;
	int handSize=0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	initializeGame(numPlayers,k,5,&G);
	deckCount = G.deckCount[player];

	G.hand[0][0] = smithy;
	printf("----- Testing Smithy Card -----\n\n");
	printf("----- Play 1 Smithy -----\n");
	handSize = G.handCount[player];
	playCard(0,0,0,0,&G);
	if(ans = assertTrue(G.handCount[player], (handSize +2)) == 1){// if our hand is 2 higher, (+3 -1 for discard)
		A_TRUE;
	}else{
		A_FALSE;
	}
	if(ans = assertTrue(G.deckCount[player], (deckCount-3)) == 1){// see if 3 cards were removed from our deck 
		A_TRUE;
	}else{
		A_FALSE;
	}
	if(ans = assertTrue(G.discardCount[player],1) == 1){ //see if we discard Smithy
		A_TRUE;
	}else{
		A_FALSE;
	}
}	
