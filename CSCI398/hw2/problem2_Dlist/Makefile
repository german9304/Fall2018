run: main.o dlist.o
	g++ -o run main.o dlist.o
dlist.o: dlist.cpp dlist.h  node.h
	g++ -Wall -pedantic -g -std=c++11 -c dlist.cpp dlist.h  node.h
main.o: main.cpp dlist.h 
	g++  -Wall -pedantic -g -std=c++11 -c main.cpp dlist.h
clean: 
	rm main.o  dlist.o run
