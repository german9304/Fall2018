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
  44083498
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
long double trapSize(int remind, int rank, long double t, int comm_sz);
void printAbsrteCriteria(long double absre);

void get_input();

int main(void)
{
    int rank, comm_sz;
    long double t, n;
    long double a, b, h, left_a, right_b;
    long double local_t, res;
    long double elapsed, startTime, endTime;
    long double total_trapezoids = 0.0;
    long double absre;
    int remind = 0;
    long double t_v = 4754.0192288588181366L;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //number of processes

    // Get User Input
    get_input(rank, &a, &b, &t);
    n = t;
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0)
    {
        startTime = MPI_Wtime();
    }
    remind = (int)t % comm_sz;

    t = trapSize(remind, rank, t, comm_sz);

    h = height(a, b, t);

    total_trapezoids = t / comm_sz;

    left_a = a + rank * total_trapezoids * h;

    right_b = left_a + total_trapezoids * h;

    local_t = trap(left_a, right_b, total_trapezoids, h);

    MPI_Reduce(&local_t, &res, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        endTime = MPI_Wtime();
        elapsed = endTime - startTime;
        absre = arte(t_v, res);
        printf("Running on %d cores\n", comm_sz);
        printf("Elapsed time = %Lf\n", elapsed);
        printf("with n = %d trapezoids, our estimate of the integral from %d to %d = %.13Le\n",
               (int)n, (int)a, (int)b, res);
        printAbsrteCriteria(absre);
    }
    /* Shut down MPI */
    MPI_Finalize();
    return 0;
}
/**
 * @brief 
 * 
 * @param absre 
 */
void printAbsrteCriteria(long double absre)
{
    if (absre > 0.5e-14L)
    {
        printf("absoule relative true error = %.19Le\n is Not less than criteria = %.19Le\n",
               absre, 0.5e-14L);
    }
    else
    {
        printf("absoule relative true error = %.19Le\n is less than criteria = %.19Le\n",
               absre, 0.5e-14L);
    }
}
/**
 * @brief 
 * 
 * @param remind 
 * @param rank 
 * @param t 
 * @param comm_sz 
 * @return long double 
 */
long double trapSize(int remind, int rank, long double t, int comm_sz)
{
    if (rank == 0)
    {
        return t + (remind) * (comm_sz - 1);
    }
    return (int)t - remind;
}
/**
 * @brief Get the input object
 * 
 * @param rank 
 * @param a 
 * @param b 
 * @param t 
 */
void get_input(int rank, long double *a, long double *b, long double *t)
{
    if (rank == 0)
    {
        printf("Enter a, b, and n\n");
        scanf("%Lf %Lf %Le", a, b, t);
        printf("\n");
    }
    MPI_Bcast(a, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(t, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
}

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @param n 
 * @param h 
 * @return long double 
 */

long double trap(long double a, long double b, long double n, long double h)
{
    long double approx = (f(b) + f(a)) / 2.0;
    //printf("n: %.14Lf\n", n);
    for (unsigned int i = 1; i <= n - 1; i++)
    {
        //printf("i: %d\n",i);
        long double ith = a + i * h;
        approx += f(ith);
        //printf("f: %Lf\n", approx);
    }
    //printf("h: %Le\n", h);
    return approx * h;
}

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @param n 
 * @return long double 
 */
long double height(long double a, long double b, int n)
{
    return (b - a) / (n);
}
/**
 * @brief 
 * 
 * @param t_v 
 * @param v_a 
 * @return long double 
 */
long double arte(long double t_v, long double v_a)
{
    long double true_error = fabsl(((t_v - v_a) / (t_v)));
    return true_error;
}

/**
 * @brief 
 * 
 * @param x 
 * @return long double 
 */
long double f(long double x)
{
    long double sqrtIn = powl((5 * sin(x / 9)) + (8 * sin(x / 2)), 4);
    return (-3 * (cosl(x / 6))) + (sqrtl(sqrtIn)) + 1;
}