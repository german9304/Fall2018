/* 
 * @file:   ptrap.c
 * @author: German Razo
 *
 * part 1 of program3
 *
 * @brief  This program uses MPI,
 *         to implement a parallel version,
 *         of the trapezoidal rule.
 *
 */
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdbool.h>

long double f(long double x);
long double height(long double a, long double b, int n);
long double arte(long double t_v, long double v_a);
long double trap(long double a, 
                long double b, 
                long double n, 
                long double h);
long double trapSize(int remind, 
                     int rank, 
                     long double t, 
                     int comm_sz);
void printAbsrteCriteria(long double absre);
void get_input(int rank, 
              long double *a, 
              long double *b, 
              long double *t,
              long double *startTime);

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

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

    MPI_Barrier(MPI_COMM_WORLD);
    get_input(rank, &a, &b, &t, &startTime);
    n = t;
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
        printf("Running on %d cores.\n", comm_sz);
        printf("Elapsed time = %Lf seconds.\n", elapsed);
        printf("with n = %d trapezoids, our estimate of the integral from %Lf to %Lf = %.13Le\n",
               (int)n, a, b, res);
        printf("true value = %.19Le\n", 4754.0192288588181366L);
        printAbsrteCriteria(absre);
    }
    /* Shut down MPI */
    MPI_Finalize();
    return 0;
}
/**
 * @brief This function prints 
 *         if the absoule relative error is less than
 *         or equal to the criteria 0.5e-14L
 * 
 * @param absre the value of abosule relative true error 
 * @return none
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
 * @brief Calculates the total number of trapezoids
 *         each process must have, 
 *         if rank is 0 , this process gets 
 *         total of trapezoids plus 
 *         the reminder of total trapezoids % total processes
 *         times total number of cores minus 1
 *         Otherwise, processes other than 0 
 *         get total trapezoids minus reminder of
 *         total trapezoids % total processes,
 *         this ensures trapezoid 0 gets even number of trapezoids
 *         and the left over trapezoids subtracted from
 *         the other processes, and the other processes 
 *         (not including 0) get even number of trapezoids. 
 *        this solves the issue when number of trapezoids
 *        are not divisible by the total number of cores. 
 *
 * 
 * @param remind value of the reminder from,
 *        total trapezoids % total processes
 * @param rank process of rank 0... n-1
 * @param t total numbe of trapezoids
 * @param comm_sz total number of processes
 * @return long double value of total number of trapezoids
 *                      each core is assigned
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
 * @brief Gets the user input: the left (a) and right endpoints (b)
 *              and the number of trapezoids (t)
 * 
 * @param rank process of rank 0..n -1
 * @param a left endpoint 
 * @param b right endpoint 
 * @param t total number of trapezoids 
 */
void get_input(int rank, 
    long double *a, 
    long double *b, 
    long double *t,
    long double *startTime)
{
    if (rank == 0)
    {
        printf("Enter a, b, and n\n");
        scanf("%Lf %Lf %Le", a, b, t);
        printf("\n");
        *startTime = MPI_Wtime();
    }
    MPI_Bcast(a, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(t, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);
}


/**
 * @brief This function estimates a define integral  
 *        using the trapezoidal method
 * 
 * @param a is the leftendpoint of the integral range 
 * @param b is the right endpoint of the integral range
 * @param n is the number of trapezoids 
 * @param h is the height value of the trapezoid
 * @return long double the result of the calculcated integral 
 */
long double trap(long double a, long double b, long double n, long double h)
{
    long double approx = (f(b) + f(a)) / 2.0;
    for (unsigned int i = 1; i <= n - 1; i++)
    {
        long double ith = a + i * h;
        approx += f(ith);
    }
    return approx * h;
}

/**
 * @brief Calculates the height of the trapezoid 
 * 
 * @param a left endpoint from range [a,b]
 * @param b right endpoint from range [a,b]
 * @param n is the number of trapezoids 
 * @return long double the height of the trapezoid 
 */
long double height(long double a, long double b, int n)
{
    return (b - a) / (n);
}
/**
 * @brief This function calculates 
 *        the absolute relative true error 
 * 
 * @param t_v is the true value 4754.0192288588181366
 * @param v_a approximation value from the trapezoidal formula
 * @return long double is the result abosule relative true error
 */
long double arte(long double t_v, long double v_a)
{
    long double true_error = fabsl(((t_v - v_a) / (t_v)));
    return true_error;
}

/**
 * @brief This function calculcates value
 *        of the function below to be integrated:
 *        -3 cos(x/6) + sqrt(pow((5 * sinl(x / 9)) + (8 * sinl(x / 2),4)) 
 *        
 * 
 * @param x value to calculate 
 * @return long double value of result function
 */
long double f(long double x)
{
    long double sqrtIn = powl((5 * sin(x / 9)) + (8 * sin(x / 2)), 4);
    return (-3 * (cosl(x / 6))) + (sqrtl(sqrtIn)) + 1;
}