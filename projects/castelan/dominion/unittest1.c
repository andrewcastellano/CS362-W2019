#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main (int argc, char *argv[]){
	struct gameState G;
	G.coins = 0;
	int bonus = 0;
	int player = 1;
	int i;
	int ans;
	printf("----- Testing updateCoins(): -----\n\n");	

	//this first test handles all off the different coin denominations
	printf("----- Different coin denominations -----\n");
	for (i = 0; i < 10; i++){
		G.handCount[player]++;
		if (i <= 3){
			G.hand[player][i] = copper;// 4 coppers
		} else if (i > 3 && i <= 7) {
			G.hand[player][i] = silver; // 4 silvers
		} else {
			G.hand[player][i] = gold; //2 gold
		}
	}
	
	updateCoins(player,&G,bonus);
	assert(G.coins == ((1 * 4) + (2 * 4) + (3 * 2)));//assert 4 coppers, 4 silvers and 2 gold is our amount
	printf("----- PASSED TEST -----\n");

	printf("----- With bonus -----\n");
	G.coins = 0;
	updateCoins(player,&G,5);//bonus of 5
	assert(G.coins == ((1 * 4) + (2 * 4) + (3 * 2) + 5));//assert 4 coppers, 4 silvers and 2 gold + 5 bonus is our amount
	printf("----- PASSED TEST -----\n");
	
	printf("----- Only silvers denomination -----\n");
	G.coins = 0;
	G.handCount[player] = 0;
	for (i = 0; i < 5; ++i){
		G.handCount[player]++;
		G.hand[player][i] = silver; // 5 silver
	}
	
	updateCoins(player,&G,bonus);
	assert(G.coins == (2 * 5));
	printf("----- PASSED TEST -----\n");

	printf("----- Zero coins no bonus -----\n");
	G.coins = 0;
	G.handCount[player] = 3;
	for (i = 0; i < 10; ++i){
		G.hand[player][i] = 0;
	}
	updateCoins(player,&G,bonus);
	assert(G.coins == 0);
	printf("----- PASSED TEST -----\n");

	printf("----- Zero coins with bonus -----\n");
	updateCoins(player,&G,25);
	assert(G.coins == 25);
	printf("----- PASSED TEST -----\n");
	
}
