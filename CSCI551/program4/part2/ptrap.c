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
#include <stdbool.h>

long double f(long double x);
long double height(long double a, long double b, int n);
bool absRelTrueErr(long double t_v, long double v_a);
long double trap(long double a, long double b, int n);

void get_input();

int main(void){
    int rank, comm_sz, t, total_trapezoids;
    long double a, b, h, left_a, right_b, starttime, endtime;
    long double local_t, res;
    starttime = 0;
    endtime = 0;
    starttime++;
    endtime++;
    // total_trapezoids = 0;
    // total_trapezoids++;
    // h = 0;
    // h++;
	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	
	// Get User Input
    get_input(rank, &a, &b, &t);
    h = height(a, b, t);   //number of processes
    //integral range for every processor
    total_trapezoids = t / comm_sz;
    left_a = a + rank * h;
    right_b = left_a + total_trapezoids *h;
    local_t = trap(left_a, right_b, t);
    //MPI_Barrier(MPI_COMM_WORLD);
    //printf("local_t: %Le\n",local_t);

    MPI_Reduce(&local_t, &res, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0){
	    printf("rank: %d\n", rank);
	   // printf("%Lf, %Lf,  %d\n", a, b, t);
	    printf("res: %.13Le\n", res);
	}
    // }else{
    //    printf("rank: %d\n", rank);
    //   // printf("%Lf, %Lf,  %d\n", a, b, t);
    //     printf("left_a: %Lf right_b: %Lf\n", left_a, right_b);
    // }
    /* Shut down MPI */
    MPI_Finalize();
	return 0;
}

void get_input(int rank, long double * a, long double * b, int * t){
    if(rank == 0){
       scanf("%Lf %Lf  %d",a, b, t);
    }
    MPI_Bcast(a, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(t, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

/*
 * Function:     height
 * Purpose:      value of function to be integrated
 *
 * Input args:   x
 *
 * Return val:   
 */

long double trap(long double a, long double b, int n){
	long double approx = (f(b) + f(a)) / 2.0;
	//printf("approx: %.14Le\n", approx);
	for(unsigned int i = 1; i <= n - 1; i++){
		//printf("i: %d\n",i);
		long double ith = a + i * height(a, b, n);
		approx += f(ith);
		//printf("f: %Lf\n", approx);
	}
	//printf("n: %d\n", n);
	return approx * height(a, b, n);
}

/*
 * Function:     height
 * Purpose:      value of function to be integrated
 *
 * Input args:   x
 *
 * Return val:   
 */
long double height(long double a, long double b, int n){
	return (b - a) / (n);
}
/*
 * Function:     absRelTrueErr
 * Purpose:      value of function to be integrated
 *
 * Input args:   prev
 *
 * Return val:   
 */
bool absRelTrueErr(long double t_v, long double v_a){
	//stoping criteria .000000000000005
	printf("t_v:%.19Le v_a: %.19Le \n",t_v, v_a);
	long double true_error = fabsl(((t_v - v_a) / (t_v))); 
	printf("error: %.14Le\n", true_error);
	return true_error <= .00000000000005L;
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