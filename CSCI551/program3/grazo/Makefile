all: tmin ptrap

tmin: tmin.c
	gcc -Wall -W -Werror -o tmin tmin.c -lm
ptrap: ptrap.c 
	mpicc -g -Wall -W -Werror -std=c99 -o ptrap ptrap.c -lm
clean: 
	rm -f tmin ptrap