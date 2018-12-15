/**
 * @file main.c
 * @author  German Razo 
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
* Allocates memory for the inner vector inside the Matrix
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
  for (int i = 0; i < n; i++)
  {
    matrix[i] = (double *)malloc(sizeof(double *) * n);
  }//for
}//initMatrixVector

/*
* 
* Prints the matrix generated 
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
      printf("%f ", matrix[i][j]);
    }//for
    printf("\n");
  }//for
}//printMatrix

/*
* 
* Generates the matrix of type double 
*  with numbers input by the user 
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
    }//for
  }//for
}//createMatrix


/*
* 
* Generates the random matrix of type double 
* when size is greater than 10, 
* in the range -1.0e3, 1.0e3 if not on the diagonal
* and range 2.0e6, 4.0e6 if non the main diagonal
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
       // matrix[i][j] = (drand48() * (1000000 - -1000000 + 1)) + -1000000;
        matrix[i][j] =  (drand48() * (1.0e6 - -1.0e6 + 1)) + -1.0e6;
        c_m[i][j] = matrix[i][j];
    }//for
  }//for
}//createRandomMatrix

/*
* 
* Initializes the starting approximation vector
* with numbers of 1.0 of type double
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
  }//for
}//initVector
/*
* 
* Prints the vector result 
*  from Jacobi and Gauss methods
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
    // printf("%.10e ", vec[i]);
    printf("%f ", vec[i]);
  }//for
  printf("\n");
}//printVector





int max_row(int n, int step, double **c_m){
  double max = fabsf(c_m[step][step]);
 // printf("step:%d\n", step);
  double row = step;
  // for (int i = 0; i < 1; i++)
  // {
  for (int i = step; i < n; i++)
  {
      double ij = fabsf(c_m[i][step]);
     // printf("%d %d\n", i, step);
      if(ij > max){
        max = ij;
        row = i;
      }
  }
  return row;
  // }
}

void copy_matrix(int n, const double ** matrix, double **c_m){
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n + 1; j++)
    {
      c_m[i][j] = matrix[i][j];
    }
  }
}
// double **swap_rows(int n, int row, int max_row, double **c_m){
  
//   int n_r = n + 1;
//   double r_t[n + 1];
 
//   for (int i = 0; i < n_r; ++i)
//   {
//     r_t[i] = c_m[row][i];
//   }
//   // printf("temp matrix\n");
//   // for (int i = 0; i < n_r; ++i)
//   // {
//   //   printf("%f ", r_t[i]);
//   // }
//   for (int i = 0; i < n_r; ++i)
//   {
//     c_m[row][i] = c_m[max_row][i];
//   }

//   for (int i = 0; i < n_r; ++i)
//   {
//     c_m[max_row][i] = r_t[i];
//   }
//   return c_m;
// }

void Swap_rows(double **a, double **b){
  double * temp = *a;
  *a = *b;
  *b = temp;
}

// double * M_d(int n, int r, double r_v, int s, double ** c_m){
//   double *mult= (double *)malloc(sizeof(double) * n + 1);
//   double *sub = (double *)malloc(sizeof(double) * n + 1);
//   for (int i = 0; i < n + 1; ++i)
//   {
//     mult[i] = (c_m[s][i] * r_v);
//     // printf("%f ", c_m[s][i]);
//   }
//    for (int i = 0; i < n + 1; ++i)
//   {
//   //  printf("%f  -  %f \n", c_m[r][i], mult[i]);
//    sub[i] = c_m[r][i] - mult[i];
//   }
//   return sub;
// }

double ** Forward_elimination(int n, int s, double **c_m, int thread_count){

  double r_v = c_m[s][s];
  int i, j;
  double div;
# pragma omp parallel for num_threads(thread_count)  \
      default(none) private(i, j, div)  shared(r_v, c_m, s, n)
  for (i = s + 1; i < n; ++i)
  {
    div = c_m[i][s]/r_v;
    //  double * r_a = M_d(n, i, div, s, c_m);
    for (j = 0; j < n + 1; j++)
    {
      // int my_rank = omp_get_thread_num();
      // printf("my_rank:%d\n", my_rank);
      c_m[i][j] = c_m[i][j] - (c_m[s][j] * div);
     // printf("i:%d j:%d \n", i, j);
    }
   //  printf("\n");
  }
 //  r_a[j];
   return c_m;
}

/**
*
* Columned oriented Back substitution
*
*/
void Back_substitution(int n, double **c_m, double *res, int thread_count){
//   double l_r = c_m[n - 1][n];
//   double p_r = c_m[n - 1][n - 1];
//   res[n - 1] = l_r/p_r;
//   int i, j;
//   double sum;
//   for (i = n - 2 ; i >=0 ; i--)
//   {
//     sum = 0.0;
// // # pragma omp parallel for num_threads(thread_count)  \
// //       default(none) private(i, j, sum)  shared(res, n, c_m)
//     for (j = n - 1;  j > i; j--)
//     {
//       sum += (((-1) * (c_m[i][j]) * res[j]));
//     }
//     sum  = (c_m[i][n] + sum)/c_m[i][i];
//     res[i] = sum;
//   }
//  printMatrix(n, c_m);
int i, j;
  for(j = n - 1; j >= 0; j--){
   // printf("%f / %f\n", c_m[j][n], c_m[j][j]);

    res[j] = c_m[j][n] / c_m[j][j];
    // printf("%f \n", c_m[j][n]);
    // printf("[%d][%d]\n", j, n);
     // printf("iter:%d. %d res:%f\n", j, j, res[j]);

# pragma omp parallel for num_threads(thread_count)  \
      default(none) private(i)  shared(j, res, c_m, n)
      for(i = j - 1 ; i >= 0; i--){
      // int my_rank = omp_get_thread_num();
       //  printf("my_rank:%d %d, %f,\n", my_rank, i, c_m[i][n], res[j]);
       // printf("%d %d %f\n", i, j-1, test[i][j-1]);
       // printf("%d, %d,  %f - %f * %f\n", i, j, c_m[i][n], c_m[i][j] , res[j]);
       c_m[i][n] = c_m[i][n] - (c_m[i][j] * res[j]);
      // printf("j:%d, i:%d, my_rank:%d\n", j, i, my_rank);
      }
   //  printf("\n");
    }
}


void Gauss_elimination(
  int n,  
  double *vec, 
  double **c_m,
  int thread_count){

  int steps = n - 1; 
  for (int s = 0; s < steps; s++)
  {
    int m_r = max_row(n, s, c_m);
    // printf("%d\n", max_row);
   // c_m = swap_rows(n, s, m_r, c_m);
    Swap_rows(&c_m[s], &c_m[m_r]);
    c_m = Forward_elimination(n, s, c_m, thread_count);
    // printf("forward elimination\n");
    // printMatrix(n, c_m);
  }
  // for (int i = 0; i < n; i++)
  // {
  //   vec[i] = 0.0;
  // }
  Back_substitution(n, c_m, vec, thread_count);
}

double Square_norm(int n, double **a, double *vec){
  double *res_vec = (double*)malloc(sizeof(double) * n);
  double euc_norm = 0.0;
  int i, j;
  for (int i = 0; i < n; i++)
  {
    res_vec[i] = 0.0;
    for (j = 0; j < n; j++)
    {
      res_vec[i] += (a[i][j] * vec[j]);
     // printf("%f * %f \n", a[i][j], vec[j]);
    }
    res_vec[i] =  res_vec[i] - a[i][j];
    euc_norm  = euc_norm + pow(res_vec[i], 2);
    // printf("i:%d, j:%d\n",i, j);
    // printf("---------\n");
  }
  // printf("euc_norm:%.10e\n", sqrt(euc_norm));
  free(res_vec);
  return sqrt(euc_norm);
}

int main(int argc, char* argv[]){
  int n = strtol(argv[1], NULL, 10);
  int thread_count = 0;
  double start_time, finish_time;
  double *vec = NULL;
  double **matrix = NULL;
  double **c_m = NULL;
  int ns = 0;
  int num_procs = omp_get_num_procs();
  if (argc > 2)
  {
    thread_count = strtol(argv[2], NULL, 10);
  }
  #pragma omp parallel num_threads(thread_count)
  {
    if (omp_get_thread_num() == 0){
      thread_count = omp_get_num_threads();
    }
  }

 

  ns = n + 1;
  c_m = (double **)malloc(sizeof(double *) * n);
  // initMatrixVector(c_m, n + 1);
 // copy_matrix(n, matrix, c_m);
  vec = (double *)malloc(sizeof(double *) * n);
  matrix = (double **)malloc(sizeof(double *) * n);

  initMatrixVector(ns, matrix); //original matrix
  initMatrixVector(ns, c_m); //augmented matrix
  initVector(n, vec); //init vector
  
  if (n < 11)
  {
    createMatrix(matrix, c_m, n, ns);
  }
  else if (n > 10)
  {
    createRandomMatrix(matrix, c_m, n, ns);
  }
 // createRandomMatrix(matrix, n, ns);
// createMatrix(matrix, c_m, n, ns);
 // printMatrix(n, matrix);
  start_time = omp_get_wtime();
  Gauss_elimination(n, vec, c_m, thread_count);
  // printf("original matrix\n");
  // printMatrix(n, matrix);
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
  // initVector(vec, n);
 
  // if (n < 11)
  // {
  //   printMatrix(matrix, n);
  //   printVector(vec, n);
  // }
  return 0;
}