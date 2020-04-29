all: dijkstra

dijkstra:	main.o
	g++ main.o -o dijkstra

main.o: main.cpp
	g++ -Wall -Wextra -pedantic -std=c++17 -c main.cpp

clean:
	-rm -f *.o dijkstra
