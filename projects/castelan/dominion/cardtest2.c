#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"
#include "string.h"
int assertTrue(int x, int y) { return x == y; }
#define A_TRUE printf("----- PASSED TEST -----\n");
#define A_FALSE printf("----- FAILED TEST -----\n");
#define TESTCARD "smithy"
	


int main(){
	struct gameState G,T;
	int ans;
	int i;
	int player = 0;
	int seed = 100;
	int preCoins;
	int preBuys;
	int preHand;
	int prePlayed;
	int deckCount;
	int playedCard;
	int handSize;
	int preDisc;
	int preDiscCard;
	int numPlayers = 2;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, council_room, feast, salvager, mine, remodel, smithy, village, baron, great_hall};
	choice1 = 1;
	initializeGame(numPlayers,k,seed,&G);
	
	printf("----- Testing card %s -----\n",TESTCARD);
	memcpy(&T,&G,sizeof(struct gameState));
	T.hand[player][0] = smithy; 
	handSize = T.handCount[player];
	deckCount = T.deckCount[player];
	preDisc = T.discardCount[player];
	preDiscCard = smithy;
	int prePhase, preTurn;
	prePhase = T.phase;
	preTurn = T.whoseTurn;
	cardEffect(smithy,choice1,choice2,choice3,&T,handpos,&bonus);
	playedCard = T.playedCards[0];
	
	if(ans = assertTrue(T.handCount[player], (handSize +2)) == 1){// if our hand is 2 higher, (+3 -1 for discard)
		A_TRUE;
	}else{
		A_FALSE;
	}
	if(ans = assertTrue(T.deckCount[player], (deckCount-3)) == 1){// see if 3 cards were removed from our deck 
		A_TRUE;
	}else{
		A_FALSE;
	}
	if(ans = assertTrue(T.discardCount[player],1) == 1){ //see if we discard 1 card
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preDiscCard,T.discard[player][0]) == 1){ //if smithy is now discarded after playing
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(prePhase,T.phase) == 1){ //assert that phase is still the same
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preTurn,T.whoseTurn) == 1){ //assert that turn is still the same
		A_TRUE;
	}else{
		A_FALSE;
	}

}	
