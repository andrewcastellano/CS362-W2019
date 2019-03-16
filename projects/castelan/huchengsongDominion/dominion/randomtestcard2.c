#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testcouncilRoom(int p, int choice1, int choice2, int choice3, int handPos, int bonus, struct gameState* post){
	struct gameState pre;
	int i,test;
	memcpy(&pre,post,sizeof(struct gameState));
	int preNumBuys,preHand,preDisc,postDisc,preDeck,postDeck,cardsTakenFromDeck,cardsInDiscardPile;
	preDisc = post->discardCount[p];//save discard count
	preDeck = post->deckCount[p];//save deck count
	preHand = post->handCount[p];//save hand count
	preNumBuys = post->numBuys;
	
	cardEffect(council_room,choice1,choice2,choice3,post,handPos,bonus);

	test = ((post->numBuys-1 == preNumBuys) == 1);//see if our numBuys increased by 1 after playing
	if (!test){
		printf("TEST FAILURE: numBuys\n");
	}

	test = ((preHand+3 == post->handCount[p]) == 1);//see if our handcount increased by 3
	if (!test){
		printf("TEST FAILURE: handCount\n");
	}

	test = ((preDeck-4 == post->deckCount[p]) == 1);
	if (!test){
		printf("TEST FAILURE: deckCount\n");
	}

	return 0;
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
		G.numPlayers=1;
		G.numBuys = 0;
		G.whoseTurn = p; // player 0's turn
		G.deckCount[p] = floor(Random() * MAX_DECK);// ensure our deck count is at most MAX_DECK
		G.discardCount[p] = floor(Random() * MAX_DECK); // ensure our discard count is at most MAX_DECK
		G.handCount[p] = floor(Random() * MAX_HAND); // ensure our hand count is at most MAX_HAND
		G.playedCardCount = floor(Random() * MAX_HAND);
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
		for (i = 0; i < G.playedCardCount; ++i){
			G.playedCards[i] = floor((Random() * treasure_map));
		}
		//call function to test feast
		
		testcouncilRoom(p,choice1,choice2,choice3,handPos,bonus,&G);

	}
}
