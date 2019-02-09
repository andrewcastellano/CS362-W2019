#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"
#include "string.h"
int assertTrue(int x, int y) { return x == y; }
#define A_TRUE printf("----- PASSED TEST -----\n");
#define A_FALSE printf("----- FAILED TEST -----\n");
#define TESTCARD "salvager"


int main(){
	struct gameState G,T;
	int ans;
	int i;
	int player = 0;
	int seed = 100;
	int preCoins;
	int preBuys;
	int preHand;
	int numPlayers = 2;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, council_room, feast, salvager, mine, remodel, smithy, village, baron, great_hall};
	choice1 = 1;
	initializeGame(numPlayers,k,seed,&G);
	
	printf("\n----- Testing card %s -----\n",TESTCARD);
	memcpy(&T,&G,sizeof(struct gameState));
	T.hand[player][0] = salvager; 
	T.hand[player][1] = feast;// card to trash
	preCoins = T.coins;
	preBuys = T.numBuys;
	preHand = T.handCount[player];
		
	cardEffect(salvager,choice1,choice2,choice3,&T,handpos,&bonus);
	

	if (ans = assertTrue(preCoins+4,(T.coins)) == 1){//coins should now be +4 because we trashed a feast card
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preBuys+1,(T.numBuys)) == 1){//salvager adds +1 buy
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(T.playedCardCount,1) == 1){//card is played
		A_TRUE;	
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(T.playedCards[player],salvager) == 1){//salvager is the card that is played
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(T.handCount[player],(preHand-2)) == 1){//hand count -2 as feast and salvager go out
		A_TRUE;
	}else{
		A_FALSE;
	}
	memcpy(&T,&G,sizeof(struct gameState));
	T.hand[player][0] = salvager;
	T.hand[player][1] = province;
	preCoins = T.coins;
	preBuys = T.numBuys;
	cardEffect(salvager,choice1,choice2,choice3,&T,handpos,&bonus);
	if (ans = assertTrue(preCoins+8,T.coins) == 1){//gain 8 for trashing province
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preBuys+1,T.numBuys) == 1){//gain 1 buy
		A_TRUE;
	}else{
		A_FALSE;
	}
}

	
