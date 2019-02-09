CFLAGS= -Wall -fpic -coverage -lm -g -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

unittestresults: 
	gcc -o unittest1 dominion.c unittest1.c rngs.c $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcc -o unittest2 dominion.c unittest2.c rngs.c $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcc -o unittest3 dominion.c unittest3.c rngs.c $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcc -o unittest4 dominion.c unittest4.c rngs.c $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcc -o cardtest1 dominion.c cardtest1.c rngs.c $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcc -o cardtest2 dominion.c cardtest2.c rngs.c $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcc -o cardtest3 dominion.c cardtest3.c rngs.c $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcc -o cardtest4 dominion.c cardtest4.c rngs.c $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov dominion.c>> unittestresults.out


interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
