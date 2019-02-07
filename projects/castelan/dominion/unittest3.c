#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"



int main(){
	struct gameState G;
	int i;
	int ans;
	int player = 1;
	printf("----- Testing fullDeckCount() -----\n\n");

	printf("----- Cards in hand, discard pile and deck\n");
	//deck = hand + discard + deck
	for (i = 0; i < 5; ++i){
		G.hand[player][i] = great_hall;
		G.handCount[player]++;
	}
	for (i = 0; i < 5; ++i){
		G.deck[player][i] = great_hall;
		G.deckCount[player]++;
	}
	for (i = 0; i < 5; ++i){
		G.discard[player][i] = great_hall;
		G.discardCount[player]++;
	}
	ans = fullDeckCount(player,great_hall,&G);
	assert(ans == 15);
	printf("----- PASSED TEST -----\n");

	printf("----- Cards in hand but not in discard pile or deck\n");
	G.handCount[player] = 0;
	G.deckCount[player] = 0;
	G.discardCount[player] = 0;
	
	for (i = 0; i < 5; ++i){
		G.hand[player][i] = great_hall;
		G.handCount[player]++;
	}
	for (i = 0; i < 5; ++i){
		G.deck[player][i] = 0;
		G.deckCount[player]++;
	}
	for (i = 0; i < 5; ++i){
		G.discard[player][i] = 0;
		G.discardCount[player]++;
	}
	ans = fullDeckCount(player,great_hall,&G);
	assert(ans == 5);
	printf("----- PASSED TEST -----\n");

	printf("----- Cards only in deck -----\n");
	G.handCount[player] = 0;
	G.deckCount[player] = 0;
	G.discardCount[player] = 0;

	for (i = 0; i < 45; ++i){
		G.deck[player][i] = great_hall;
		G.deckCount[player]++;
	}
	ans = fullDeckCount(player,great_hall,&G);
	assert(ans == 45);
	printf("----- PASSED TEST -----\n");

	G.deckCount[player] = 0;
	printf("----- Nothing in hand, discard, or deck -----\n");
	ans = fullDeckCount(player,great_hall,&G);
	assert(ans == 0);
	printf("----- PASSED TEST -----\n");

}


