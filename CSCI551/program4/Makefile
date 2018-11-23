all: matrixmult matrix_mpi mpi_mat_vect_mult

matrixmult: matrixmult.c
	mpicc -g -Wall -std=c99 -o matrixmult matrixmult.c 
matrix_mpi: matrix_mpi.c 
	mpicc -g -Wall -std=c99 -o matrix_mpi matrix_mpi.c 
mpi_mat_vect_mult: mpi_mat_vect_mult.c 
	mpicc -g -Wall -std=c99 -o mpi_mat_vect_mult mpi_mat_vect_mult.c 
clean: 
	rm -f matrixmult matrix_mpi mpi_mat_vect_mult