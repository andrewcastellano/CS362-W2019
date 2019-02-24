CFLAGS= -Wall -fpic -coverage -lm -std=c99

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

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

	gcc -o rt -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)


randomtests:
	#gcc -o rta -g dominion.c rngs.c randomtestadventurer.c $(CFLAGS)
	#./rta >> randomtestadventurer.out
	#gcov -b dominion.c >> randomtestadventurer.out
	gcc -o rt1 -g dominion.c rngs.c randomtestcard1.c $(CFLAGS)
	./rt1 >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	#gcc -o rt2 -g dominion.c rngs.c randomtestcard2.c $(CFLAGS)
	#./rt2 >> randomtestcard2.out
	#gcov -b dominion.c >> randomtestcard2.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe rt1 rt2 rta *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
