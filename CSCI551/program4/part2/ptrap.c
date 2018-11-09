/* 
 * File:   ptrap.c
 * Author: German Razo
 *
 * part 2
 * From o244-01 to o244-10
 * Purpose:  
 *  
 *  43999999
 * 43804687  cel:44500000 mid:44152343.5000000000000
  l:43804687 
 *
 *
 */
#include <stdio.h>
#include <mpi.h>
#include <math.h> 
#include <stdbool.h>

long double f(long double x);
long double height(long double a, long double b, int n);
long double arte(long double t_v, long double v_a);
long double trap(long double a, long double b, long double n, long double h);

void get_input();

int main(void){
    int rank, comm_sz;
    long double  t, n;
    long double a, b, h, left_a, right_b, starttime, endtime;
    long double local_t, res;
    long double  elapsed;
    long double total_trapezoids = 0.0;
    long double absre;
    int remind = 0;
    long double t_v = 4754.0192288588181366L;
    // total_trapezoids = 0;
    // total_trapezoids++;
    // h = 0;
    // h++;
	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);   //number of processes
	
	// Get User Input
    get_input(rank, &a, &b, &t);
    n = t;
    MPI_Barrier(MPI_COMM_WORLD);
     if(rank == 0)
    {
      starttime = MPI_Wtime();
    }
    remind = (int)t % comm_sz;

    // if(rank == 0){

    //   // printf("reminder: %d\n", remind);
    // }
    //t = (int) t - remind;
    //if(){
        
        if(rank == 0 ){
            t = t + (remind) * (comm_sz - 1);
        }else{
            t = (int) t - remind;
        }
        h = height(a, b, t); 
    //}
   // printf("before local_t: %Lf  rank:%d, total_trapezoids:%Lf\n",t, rank, total_trapezoids);
    //printf(" local_t: %Lf  rank:%d, total_trapezoids:%Lf\n",t, rank, total_trapezoids);
    total_trapezoids = t / comm_sz;
    left_a = a + rank * total_trapezoids * h;
    right_b = left_a + total_trapezoids  * h;
    local_t = trap(left_a, right_b, total_trapezoids, h);
    MPI_Reduce(&local_t, &res, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        endtime = MPI_Wtime();
        elapsed = endtime - starttime;
          //printf("loc_elapsed = %Lf rank:%d\n",elapsed, rank);
       // endtime = MPI_Wtime();
       // printf("res:%.19Le\n",res);
     absre =  arte(t_v, res);
     printf("Running on %d cores\n", comm_sz);
     printf("Elapsed time = %Lf\n", elapsed);
    // printf("starttime = %Lf\n", starttime);
     printf("with n = %d trapezoids, our estimate of the integral from %d to %d = %.13Le\n", 
        (int) n, (int) a, (int) b, res);
    // printf("true value = %.19Le\n", t_v);
     if(absre > 0.5e-14L){
       printf("absoule relative true error = %.19Le\n is Not less than criteria = %.19Le\n", 
        absre, 0.5e-14L);
      // printf("true value = %.19Le\n", t_v);
     }else{
          printf("absoule relative true error = %.19Le\n is less than criteria = %.19Le\n", 
        absre, 0.5e-14L);
     }
     // printf("absoule relative true error %.19Le\n", absre);
     // printf("criteria = %.19Le\n", .00000000000005L);  

    }
    /* Shut down MPI */
    MPI_Finalize();
	return 0;
}

void get_input(int rank, long double * a, long double * b, long double * t){
    if(rank == 0){
       printf("Enter a, b, and n\n");
       scanf("%Lf %Lf %Le",a, b, t);
       printf("\n");
       //printf("%Lf %Lf %Lf\n",*a, *b, *t);
    }
    MPI_Bcast(a, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(t, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
}

/*
 * Function:     height
 * Purpose:      value of function to be integrated
 *
 * Input args:   x
 *
 * Return val:   
 */

long double trap(long double a, long double b, long double n, long double h){
	long double approx = (f(b) + f(a)) / 2.0;
	//printf("n: %.14Lf\n", n);
	for(unsigned int i = 1; i <= n - 1; i++){
		//printf("i: %d\n",i);
		long double ith = a + i * h;
		approx += f(ith);
		//printf("f: %Lf\n", approx);
	}
	//printf("h: %Le\n", h);
	return approx * h;
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
long double arte(long double t_v, long double v_a){
	//stoping criteria .000000000000005
	//printf("t_v:%.19Le v_a: %.19Le \n",t_v, v_a);
	long double true_error = fabsl(((t_v - v_a) / (t_v))); 
	//printf("error: %.14Le\n", true_error);
	// return true_error <= .00000000000005L;
    return true_error;
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