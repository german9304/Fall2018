/* 
 * File:   ptrap.c
 * Author: German Razo
 *
 * part 2
 * 
 * Purpose:  
 *
 *
 */
#include <stdio.h>
#include <mpi.h>
#include <math.h> 

long double f(long double x);
void get_input();

int main(void){
    int rank, comm_sz;
    long double a, b, h, left_endpt, right_endpt;
    

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	 /* Shut down MPI */
    MPI_Finalize();
	return 0;
}

/*
 * Function:     f
 * Purpose:      value of function to be integrated
 *
 * Input args:   x
 *
 * Return val:   
 */
long double f(long double x){
 long double sqrtIn = powl((5 * sin(x / 9)) + (8 * sin(x / 2)), 4);
 return (-3 * (cosl(x / 6))) + (sqrtl(sqrtIn)) + 1;
}