#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"



int main(){
	struct gameState G;
	int i;
	int ans;

	printf("----- Testing supplyCount() -----\n");

	printf("----- 10 supply -----\n");
	G.supplyCount[copper] = 10;
	ans = supplyCount(copper,&G);
	assert(ans == 10);
	printf("----- PASSED TEST -----\n");
	
	printf("----- 0 supply -----\n");
	G.supplyCount[copper] = 0;
	ans = supplyCount(copper,&G);
	assert(ans == 0);
	G.supplyCount[silver] = 0;
	ans = supplyCount(silver,&G);
	assert(ans == 0);
	printf("----- PASSED TEST -----\n");

	printf("----- Negative supply -----\n");
	G.supplyCount[gold] = -10;
	ans = supplyCount(gold,&G);
	assert(ans == -10);
	printf("----- PASSED TEST -----\n");


	printf("----- High supply -----\n");
	G.supplyCount[province] = 500;
	ans = supplyCount(province,&G);
	assert(ans == 500);
	printf("----- PASSED TEST -----\n");


}
