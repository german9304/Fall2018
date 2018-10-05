run: main.o list.o
	g++ -o run main.o list.o
list.o: list.cpp list.h node.h
	g++ -c -Wall -pedantic -g -std=c++11 list.cpp
main.o: main.cpp list.h 
	g++ -c -Wall -pedantic -g -std=c++11 main.cpp
clean: 
	rm main.o list.o run
