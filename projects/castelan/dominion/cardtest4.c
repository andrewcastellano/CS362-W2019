#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"
#include "string.h"

int assertTrue(int x, int y) { return x == y; }
#define A_TRUE printf("----- PASSED TEST -----\n");
#define A_FALSE printf("----- FAILED TEST -----\n");
#define TESTCARD "baron"


int main(){
	struct gameState G,T;
	int ans;
	int i;
	int player = 0;
	int seed = 100;
	int preCoins;
	int preBuys;
	int preHand;
	int preDisc;
	int numPlayers = 2;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, council_room, feast, salvager, mine, remodel, smithy, village, baron, great_hall};
	choice1 = 1;
	initializeGame(numPlayers,k,seed,&G);
	
	printf("\n----- Testing card %s -----\n",TESTCARD);
	memcpy(&T,&G,sizeof(struct gameState));
	T.hand[player][0] = baron;
	T.hand[player][1] = estate;
	preBuys = T.numBuys;
	preDisc = T.discardCount[player];
	preCoins = T.coins;
	//bool to discard estate set to true
	cardEffect(baron,choice1,choice2,choice3,&T,handpos,&bonus);

	if (ans = assertTrue(preDisc+1,T.discardCount[player]) == 1){//discard count goes up by 1
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preBuys+1, T.numBuys) == 1){
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(T.hand[player][1],estate) == 0){//Hand at position 1 is no longer an estate because of baron
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(T.discardCount[player],1) == 1){//discard count goes up by 1
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(T.discard[player][0],estate) == 1){//discarded card is an estate
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preCoins + 4,T.coins) == 1){ //num coins +4
		A_TRUE;
	}else{
		A_FALSE;
	}
	memcpy(&T,&G,sizeof(struct gameState));
	T.hand[player][0] = baron;
	choice1 = 0;
	preCoins = T.coins;
	preBuys = T.numBuys;
	preDisc = T.discardCount[player];
	int preSupp;
	preSupp = T.supplyCount[estate];
	//bool to discard estate set to false
	cardEffect(baron,choice1,choice2,choice3,&T,handpos,&bonus);
	
	if (ans = assertTrue(preDisc+1,T.discardCount[player]) == 1){//discard count goes up by 1
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(T.discard[player][0],estate) == 1){ //gain estate in discard pile
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preSupp-2,T.supplyCount[estate]) == 1){//supply count for estate decreased
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preBuys+1,T.numBuys) == 1){ //numbuys went up by 1
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preCoins,T.coins) == 1){ //coins remained the same because we did not discard an estate
		A_TRUE;
	}else{
		A_FALSE;
	}

}	
