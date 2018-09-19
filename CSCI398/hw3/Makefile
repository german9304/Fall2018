run: main.o  bst.o 
	g++ -o run main.o  bst.o 
bst.o: bst.cpp bst.h  tnode.h
	g++ -c -Wall -pedantic -g -std=c++11 bst.cpp
main.o: main.cpp  bst.h 
	g++ -c -Wall -pedantic -g -std=c++11 main.cpp
clean: 
	rm main.o bst.o run
