black_jack: black_jack.o cards.o deck.o players.o dealer.o
	g++ -Wall  -pedantic -g -std=c++20 -o black_jack black_jack.o cards.o deck.o players.o dealer.o -lncurses

black_jack.o: black_jack.cpp 
	g++ -Wall -pedantic -g -std=c++20 -c black_jack.cpp

cards.o: cards.cpp cards.h
	g++ -Wall  -pedantic -g -std=c++20 -c cards.cpp

deck.o: deck.cpp deck.h
	g++ -Wall  -pedantic -g -std=c++20 -c deck.cpp

players.o: players.cpp players.h
	g++ -Wall  -pedantic -g -std=c++20 -c players.cpp

dealer.o: dealer.cpp dealer.h
	g++ -Wall  -pedantic -g -std=c++20 -c dealer.cpp

clean:
	rm -f *o black_jack black_jack.o cards.o deck.o players.o dealer.o

