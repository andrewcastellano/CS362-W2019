#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testSmithy(int p, int choice1, int choice2, int choice3, int handPos, int bonus, struct gameState* post){
	struct gameState pre;
	int i,test;
	memcpy(&pre,post,sizeof(struct gameState));

	int preHand,preDisc;
	preDisc = post->discardCount[p];//save discard count
	preHand = post->handCount[p];//save hand count
	cardEffect(smithy,choice1,choice2,choice3,post,handPos,bonus);

	test = ((preHand == post->handCount[p] - 2) == 1);//ensure we have 2 more in our hand now +3 for drawn and -1 for discard
	if (!test){
		printf("TEST FAILURE: Handcount after playing smithy\n"); 
	}

	test = ((preDisc == post->discardCount[p] + 1) == 1);//ensure we are adding 1 to the discard pile after playing
	if (!test){
		printf("TEST FAILURE: Discard count after playing smithy\n");
	}
}


int main(){
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, salvager, mine, remodel, smithy, village, baron, great_hall};
	int i, n, p, choice1, choice2, choice3, bonus, handPos;
	
  SelectStream(2);
  PutSeed(3);

	for (n = 0; n < 2000; ++n){
		for (i = 0; i < sizeof(struct gameState); ++i){
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = floor(Random() * 2); //players
		G.whoseTurn = p; // player 0's turn
		G.deckCount[p] = floor(Random() * MAX_DECK);// ensure our deck count is at most MAX_DECK
		G.discardCount[p] = floor(Random() * MAX_DECK); // ensure our discard count is at most MAX_DECK
		G.handCount[p] = floor(Random() * MAX_HAND); // ensure our hand count is at most MAX_HAND
		choice1, choice2, choice3, bonus = 0;//no choices or bonus for adventurer card
		handPos = G.handCount[p];
		
		//randomly set the deck, discard, and hand
	
		for (i = 0; i < G.deckCount[p]; ++i){
			G.deck[p][i] = floor((Random() * treasure_map));//random cards in deck for current player
			//printf("G.deck[i] %d\n",G.deck[p][i]);
		}
		for (i = 0; i < G.discardCount[p]; ++i){
			G.discard[p][i] = floor((Random() * treasure_map));//random cards in discard for current player
			//printf("G.discard[i] %d\n",G.discard[p][i]);

		}
		for (i = 0; i < G.handCount[p]; ++i){
			G.hand[p][i] = floor((Random() * treasure_map));//random cards in hand for current player
			//printf("G.hand[i] %d\n",G.hand[p][i]);
		}

		//call function to test adventurer
		testSmithy(p,choice1,choice2,choice3,handPos,bonus,&G);
	}
}
