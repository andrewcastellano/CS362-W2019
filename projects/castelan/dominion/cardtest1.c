#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"
#include "string.h"
int assertTrue(int x, int y) { return x == y; }
#define A_TRUE printf("----- PASSED TEST -----\n");
#define A_FALSE printf("----- FAILED TEST -----\n");
#define TESTCARD "adventurer"


int main(){
	struct gameState G,T;
	int ans;
	int i;
	int player = 0;
	int seed = 100;
	int preCoins;
	int preBuys;
	int numPlayers = 2;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, council_room, feast, salvager, mine, remodel, smithy, village, baron, great_hall};
	choice1 = 0;
	initializeGame(numPlayers,k,seed,&G);
	
	printf("\n----- Testing card %s -----\n",TESTCARD);
	memcpy(&T,&G,sizeof(struct gameState));
	for (i = 0; i < 10; ++i){
		if (i < 7){
			T.deck[player][i] = copper;
		}else{
			T.deck[player][i] = feast;
		}
	}
	for (i = 0; i < 5; ++i){
		T.hand[player][i] = feast;//make whole hand of feasts
	}
	int preHandCount,preDeckCount,preDiscCard,preDiscCount;
	
	preHandCount = T.handCount[player];//store hand count
	preDiscCount = T.discardCount[player];
	T.deckCount[player] = 10;
	preDeckCount = 10;	
	cardEffect(adventurer,choice1,choice2,choice3,&T,handpos,&bonus);
	
	if (ans = assertTrue(preHandCount+2,T.handCount[player]) == 1){//should have 2 more coins in hand here
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preDeckCount-5,T.deckCount[player]) == 1){//deck should have 5 less cards given current deck count. 2 for the coins taken and 3 for the feasts
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preDiscCount+3,T.discardCount[player]) == 1){ //discount pile should now have 3 in current setup of deck
		A_TRUE;
	}else{
		A_FALSE;
	}

	memcpy(&T,&G,sizeof(struct gameState));
	T.deck[player][0] = copper;
	T.deck[player][1] = copper;
	T.deck[player][2] = copper;
	T.deck[player][3] = copper;
	T.deck[player][4] = copper;
	T.deck[player][5] = feast;
	T.deck[player][6] = feast;
	T.deck[player][7] = copper;
	T.deck[player][8] = feast;
	T.deck[player][9] = copper;
	T.deckCount[player] = 10;
	preDiscCount = T.discardCount[player];
	preDeckCount = 10;
	preHandCount = T.handCount[player];
	cardEffect(adventurer,choice1,choice2,choice3,&T,handpos,&bonus);
	if (ans = assertTrue(preHandCount+2,T.handCount[player]) == 1){//should have 2 more coins in hand now
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preDeckCount-3,T.deckCount[player]) == 1){//given current deck should have 3 less now
		A_TRUE;
	}else{
		A_FALSE;
	}
	if (ans = assertTrue(preDiscCount+1,T.discardCount[player]) == 1){//1 card should now be discarded
		A_TRUE;
	}else{
		A_FALSE;
	}


/*

	printf("----- Testing Adventurer Card -----\n\n");
	printf("----- 2 total treasures in deck -----\n");
	G.deckCount[player] = 10;//total count of deck size
	//creates hand of 1 adventurer, 2 copper, and 7 provinces
			G.deck[player][0] = adventurer;
			for(i = 1; i < 10; ++i){
				if (i < 3){
					G.deck[player][i] = copper;
				}else{
					G.deck[player][i] = province;
				}
			}
	G.handCount[player] = 1;
	G.hand[0][0] = adventurer;//place adventurer in hand
	playCard(0,0,0,0,&G);//play adventurer
	if(ans = assertTrue(G.handCount[player],3) == 1 ){//should have 3 cards inhand
		A_TRUE;
	}else{
		A_FALSE;
	}	
	if(ans = assertTrue(G.discardCount[player],8) == 1){//8 cards (all except the 2 coppers) are in discard pile
		A_TRUE;
	}else{
		A_FALSE;
	}


	printf("----- 3 total treasures in deck -----\n");
	for(i = 1; i < 10; ++i){
		if (i < 4){
			G.deck[player][i] = copper;
		}else{
			G.deck[player][i] = province;
		}
	}
	G.discardCount[player] = 0;
	G.handCount[player] = 1;
	G.hand[0][0] = adventurer;//place adventurer in hand
	playCard(0,0,0,0,&G);//play adventurer
	if(ans = assertTrue(G.handCount[player],3) == 1){//should have 3 cards in hand
		A_TRUE;
	}else{
		A_FALSE;
	}
	if(ans = assertTrue(G.discardCount[player],8) == 1){//8 cards (all except the 2 coppers) are in discard pile
		A_TRUE;
	}else{
		A_FALSE;
	}
	
	
	printf("----- 4 total treasures in deck -----\n");
	for(i = 1; i < 10; ++i){
		if (i < 5){
			G.deck[player][i] = copper;
		}else{
			G.deck[player][i] = province;
		}
	}
	G.discardCount[player] = 0;
	G.handCount[player] = 1;
	G.hand[0][0] = adventurer;//place adventurer in hand
	playCard(0,0,0,0,&G);//play adventurer
	if(ans = assertTrue(G.handCount[player],3) == 1){//should have 3 cards in hand
		A_TRUE;
	}else{
		A_FALSE;
	}
	if(ans = assertTrue(G.discardCount[player],8) == 1){//8 cards (all except the 2 coppers) are in discard pile
		A_TRUE;
	}else{
		A_FALSE;
	}
	
	printf("----- 0 total treasures in deck -----\n");
	for(i = 1; i < 10; ++i){
			G.deck[player][i] = province;
		}
	G.discardCount[player] = 0;	
	G.handCount[player] = 1;
	G.hand[0][0] = adventurer;//place adventurer in hand
	playCard(0,0,0,0,&G);//play adventurer
	if(ans = assertTrue(G.handCount[player],1) == 1){//should have 1 card in hand
		A_TRUE;
	}else{
		A_FALSE;
	}
	if(ans = assertTrue(G.discardCount[player],0) == 1){// 0 discarded
		A_TRUE;
	}else{
		A_FALSE;
	}
	*/
}
