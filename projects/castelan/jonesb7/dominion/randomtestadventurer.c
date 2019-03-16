#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testAdventurer(int p, int choice1, int choice2, int choice3, int handPos, int bonus, struct gameState* post){
	struct gameState pre;
	int i,test;
	memcpy(&pre,post,sizeof(struct gameState));

	int preHand,preDisc,postDisc,preDeck,postDeck,cardsTakenFromDeck,cardsInDiscardPile;
	preDisc = post->discardCount[p];//save discard count
	preDeck = post->deckCount[p];//save deck count
	preHand = post->handCount[p];//save hand count

	cardEffect(adventurer,choice1,choice2,choice3,post,handPos,bonus);

	postDisc = post->discardCount[p];//save discard count after
	postDeck = post->deckCount[p];//save deck counte after
	
	//(pre deck count - post deck count) -  (post discard count - pre discard count + 2)should be 0 if we took 2 cards
	cardsTakenFromDeck = (preDeck - postDeck);
	cardsInDiscardPile = (postDisc - preDisc);
	test = (cardsTakenFromDeck - (cardsInDiscardPile+2) == 0 ? 1: 0);//we took 2 cards out
	if (!test){
		printf("TEST FAILURE: Deck and discard counts are appropriate after playing adventurer\n");
	}

	//hand count should be -2
	test = (preHand == post->handCount[p] - 2) ? 1: 0;//true if they evaluated 2 cards more in hand or false otherwise
	if (!test){//if we passed the test
		printf("TEST FAILURE: Handcount 2 higher after playing adventurer \n");
	}

	//change pre's cards to mirror post
	//test if the rest of the struct is unchanged
	for (i = 0; i < post->deckCount[p]; ++i){
		pre.deck[p][i] = post->deck[p][i];//copy cards over
	}
	for (i = 0; i < post->discardCount[p]; ++i){
		pre.discard[p][i] = post->discard[p][i];
	}
	for (i = 0; i < post->handCount[p]; ++i){
		pre.hand[p][i] = post->hand[p][i];
	}
	pre.handCount[p] = post->handCount[p];
	pre.deckCount[p] = post->deckCount[p];
	pre.discardCount[p] = post->discardCount[p];
	test = (memcmp(&pre,post,sizeof(struct gameState)) == 0);//check if both of our game states are identical
	if (!test){
		printf("TEST FAILURE: gameState has been altered\n");
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
		testAdventurer(p,choice1,choice2,choice3,handPos,bonus,&G);
	}
}
