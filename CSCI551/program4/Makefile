all: matrixmult matrix_mpi mpi_mat_vect_mult test

matrixmult: matrixmult.c
	mpicc -g -std=c99 -o matrixmult matrixmult.c 
matrix_mpi: matrix_mpi.c 
	mpicc -g  -std=c99 -o matrix_mpi matrix_mpi.c 
mpi_mat_vect_mult: mpi_mat_vect_mult.c 
	mpicc -g -Wall -W -Werror -std=c99 -o mpi_mat_vect_mult mpi_mat_vect_mult.c 
test: mpi_mat_vect_mult.c 
	mpicc -g -std=c99 -o test test.c 
clean: 
	rm -f matrixmult matrix_mpi mpi_mat_vect_mult