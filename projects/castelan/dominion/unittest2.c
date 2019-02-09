#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"


int main(){
	struct gameState G;
	int i;
	int ans;
	printf("\n----- Testing isGameOver() -----\n");
	
	printf("----- 0 provinces -----\n");
	G.supplyCount[province] = 0;
	ans = isGameOver(&G);
	assert(ans == 1); // game is over
	printf("----- PASSED TEST -----\n");

	printf("----- 3 supply piles set to 0 -----\n");
	for (i = curse; i < treasure_map +1; i++){
		if (i < 3){
			G.supplyCount[i] = 0; //set 3 to 0
		}else{
			G.supplyCount[i] = 1;
		}
	}
	ans = isGameOver(&G);
	assert(ans == 1); //game is over
	printf("----- PASSED TEST -----\n");

	
	printf("----- 3 different supply piles set to 0 -----\n");
	for (i = curse; i < treasure_map +1; i++){
		if (i < 10 && i > 6){ // 7-9 are 0
			G.supplyCount[i] = 0;
		}else{
			G.supplyCount[i] = 1;
		}
	}
	ans = isGameOver(&G);
	assert(ans == 1); // game is over
	printf("----- PASSED TEST -----\n");
	
	
	printf("----- 1 province remains -----\n");
	//there will be 1 province and 2 of every other card
	G.supplyCount[province] = 1;
	for (i = curse; i < treasure_map +1; i++){
		if (i == province){
			G.supplyCount[i] = 1;
		}else{
			G.supplyCount[i] = 2;
		}
	}
	ans = isGameOver(&G);
	assert(ans == 0); // game is not over
	printf("----- PASSED TEST -----\n");

	printf("----- 2 piles (not including province) have 0 -----\n");
	for (i = curse; i < treasure_map +1; i++){
		if (i > salvager){//last 2 cards only
			G.supplyCount[i] = 0;
		}else{
			G.supplyCount[i] = 1; //every other card has 1
		}
	}
	ans = isGameOver(&G);
	assert(ans == 0); // game is not over
	printf("----- PASSED TEST -----\n");

	printf("----- Each pile has 5 cards -----\n");
	for (i = curse; i < treasure_map +1; i++){
		G.supplyCount[i] = 5;
	}
	ans = isGameOver(&G);
	assert(ans == 0); // game is not over
	printf("----- PASSED TEST -----\n");
}
