/**
 * @file gauss.c
 * @author  German Razo 
 *
 * @brief This program implements a parallel version
 *        of Gaussian elimination with partial pivoting.
 *
 *   
 *
 */
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <omp.h>

/*
* 
* @brief Allocates memory 
*        for the inner vector inside the augmented Matrix
* 
* @param matrix is a double pointer array
*
* @param n size of the double pointer matrix 
* 
* @return none 
*
*/
void initMatrixVector(int n, double **matrix)
{
  for (int i = 0; i < n - 1; i++)
  {
    matrix[i] = (double *)malloc(sizeof(double *) * n);
  } //for
} /* initMatrixVector */

/*
* 
* @brief Prints the augmented matrix generated 
* by user when n is less than 11
* 
* @param matrix is a double pointer array
*
* @param n size of the double pointer matrix 
* 
* @return none 
*
*/
void printMatrix(int n, double **matrix)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n + 1; j++)
    {
      printf("%.10e ", matrix[i][j]);
    } //for
    printf("\n");
  } //for
} /* printMatrix */

/*
* 
* @brief Generates the augmented matrix of type double 
*  with numbers input by the user, 
*  when n is less than 11.
* 
* @param matrix is a double pointer array
*
* @param n is size of the double pointer matrix 
* 
* @param ns is the size of the double pointer matrix 
*
*
* @return none 
*
*/
void createMatrix(double **matrix, double **c_m, int n, int ns)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < ns; j++)
    {
      scanf("%lf", &matrix[i][j]);
      c_m[i][j] = matrix[i][j];
    } //for
  }   //for
} /* createMatrix */

/*
* 
* @brief Generates the random augmented matrix of type double 
* when size is greater than 10, 
* with numbers in the range -1.0e6, 1.0e6. 
* 
* @param matrix is a double pointer array
*
* @param n is size of the double pointer matrix 
* 
* @param ns is the size of the double pointer matrix 
*
*
* @return none 
*
*/
void createRandomMatrix(double **matrix, double **c_m, int n, int ns)
{
  srand48(time(0));
  for (int i = 0; i < n; i++)
  {

    for (int j = 0; j < ns; j++)
    {
      matrix[i][j] = (drand48() * (1.0e6 - -1.0e6 + 1)) + -1.0e6;
      c_m[i][j] = matrix[i][j];
    } //for
  }   //for
} /* createRandomMatrix */

/*
* 
* Initializes the starting approximation vector
* with numbers of 0.0 of type double
* 
* @param vec is an array of type double
*
* @param n size of the double pointer matrix 
* 
* @return none 
*
*/
void initVector(int n, double *vec)
{
  for (int i = 0; i < n; i++)
  {
    vec[i] = 0.0;
  } //for
} /* initVector */
/*
* 
* Prints the result vector 
*  from Gauss method
* 
* @param vec is an array of type double
*
* @param n size of the double pointer matrix 
* 
* @return none 
*
*/
void printVector(int n, double *vec)
{
  for (int i = 0; i < n; i++)
  {
    printf("%.10e ", vec[i]);
  } //for
  printf("\n");
} /* printVector */

/**
 * @brief Selects the best row with maximum number,
 *   this is the first step or partial pivoting.
 * 
 * @param n size of augmented matrix
 * @param step step of the outer for loop, 
 *        steps are n - 1; 
 * @param c_m is matrix to where the best row
 *            will be found.
 * @return int returns the maximum row from the matrix.
 */
int Max_row(int n, int step, double **c_m)
{
  double max = fabsf(c_m[step][step]);
  double row = step;
  for (int i = step; i < n; i++)
  {
    double ij = fabsf(c_m[i][step]);
    if (ij > max)
    {
      max = ij;
      row = i;
    } //if
  }   //for
  return row;
} /* Max_row */

/**
 * @brief swaps two rows by addresses.
 *      this is second step of parial privoting.
 * 
 * @param a row a to be swapped 
 * @param b row b to be swapped
 */
void Swap_rows(double **a, double **b)
{
  double *temp = *a;
  *a = *b;
  *b = temp;
} /* swap_rows */

/**
 * @brief Implements parallel version for forward elimination
 *      from gauss elimination method. 
 *       privates and shared variables are set and defautl is none,
 *       variables i , j and div are private, and 
 *       shared variables are r_v , c_m , s and n
 * 
 * @param n size of the augmented matrix
 * @param s step number from gauss elimination
 * @param c_m the copy of original augmented matrix
 * @return double** 
 */
double **Forward_elimination(int n, int s, double **c_m, int thread_count)
{
  double r_v = c_m[s][s];
  int i, j;
  double div;
#pragma omp parallel for num_threads(thread_count) \
        default(none) private(i, j, div) shared(r_v, c_m, s, n)
  for (i = s + 1; i < n; ++i)
  {
    div = c_m[i][s] / r_v;
    for (j = 0; j < n + 1; j++)
    {
      c_m[i][j] = c_m[i][j] - (c_m[s][j] * div);
    }
  }
  return c_m;
} /* Forward_elimination */

/**
 * @brief Implemetes parallel version of back susbtitution
 *        in column oriented from the gauss elimination. 
 *        private and shared variables are set, 
 *        private variable is i and shared variables 
 *         are j, res, c_m and n.
 * 
 * @param n size of augmented matrix
 * @param c_m copy of the augmented matrix
 * @param res vector where the result of the unknowns 
 *        will be stored.
 */
void Back_substitution(int n, double **c_m, double *res, int thread_count)
{
  int i, j;
  for (j = n - 1; j >= 0; j--)
  {
    res[j] = c_m[j][n] / c_m[j][j];
#pragma omp parallel for num_threads(thread_count) \
        default(none) private(i) shared(j, res, c_m, n)
    for (i = j - 1; i >= 0; i--)
    {
      c_m[i][n] = c_m[i][n] - (c_m[i][j] * res[j]);
    }
  }
} /* Back_substitution */
/**
 * @brief Implements Gauss elimination method
 *       to find unknowns.
 * 
 * @param n size of augmented matrix 
 * @param vec vector of type double where result of
 *            unknowns will be stored.
 * @param c_m copy of augmented matrix.
 */
void Gauss_elimination(
    int n,
    double *vec,
    double **c_m,
    int thread_count)
{

  int steps = n - 1;
  for (int s = 0; s < steps; s++)
  {
    int m_r = Max_row(n, s, c_m);
    Swap_rows(&c_m[s], &c_m[m_r]);
    c_m = Forward_elimination(n, s, c_m, thread_count);
  }
  Back_substitution(n, c_m, vec, thread_count);
} /* Gauss_elimination */
/**
 * @brief implemented the l2 norm
 *        of the residual vector from Ax - b
 * 
 * @param n size of augmented matrix
 * @param a the augmented matrix
 * @param vec vector with the result values 
 *         from the unknowns 
 * @return double the resul of the l2 norm.
 */
double Square_norm(int n, double **a, double *vec)
{
  double *res_vec = (double *)malloc(sizeof(double) * n);
  double euc_norm = 0.0;
  int i, j;
  for (int i = 0; i < n; i++)
  {
    res_vec[i] = 0.0;
    for (j = 0; j < n; j++)
    {
      res_vec[i] += (a[i][j] * vec[j]);
    }
    res_vec[i] = res_vec[i] - a[i][j];
    euc_norm = euc_norm + pow(res_vec[i], 2);
  }
  free(res_vec);
  return sqrt(euc_norm);
} /* Square_norm */

int main(int argc, char *argv[])
{
  int n = strtol(argv[1], NULL, 10);
  int thread_count = 0;
  double start_time, finish_time;
  double *vec = NULL;
  double **matrix = NULL;
  double **c_m = NULL;
  int ns = 0;
  int num_procs = omp_get_num_procs();
# pragma omp parallel 
  {
    thread_count = omp_get_num_threads();
  }

  ns = n + 1;
  c_m = (double **)malloc(sizeof(double *) * n);
  vec = (double *)malloc(sizeof(double *) * n);
  matrix = (double **)malloc(sizeof(double *) * n);

  initMatrixVector(ns, matrix); //original matrix
  initMatrixVector(ns, c_m);    //augmented matrix
  initVector(n, vec);           //init vector

  if (n < 11)
  {
    createMatrix(matrix, c_m, n, ns);
  }
  else if (n > 10)
  {
    createRandomMatrix(matrix, c_m, n, ns);
  }

  start_time = omp_get_wtime();
  Gauss_elimination(n, vec, c_m, thread_count);
  finish_time = omp_get_wtime();
  double s_r = Square_norm(n, matrix, vec);
  if (n < 11)
  {
    printMatrix(n, matrix);
    printVector(n, vec);
  }

  printf("Number of processors = %d\n", num_procs);
  printf("Number of threads = %d\n", thread_count);
  printf("Elapsed time = %f seconds\n", finish_time - start_time);
  printf("L2-norm residual = %.10e\n", s_r);
  return 0;
}