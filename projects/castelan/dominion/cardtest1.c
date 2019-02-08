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
	int player = 0;
	int i;
	int numPlayers = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	initializeGame(numPlayers,k,5,&G);

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
}
