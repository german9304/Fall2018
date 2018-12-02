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
void initMatrixVector(double **matrix, int n)
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
void printMatrix(double **matrix, int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n + 1; j++)
    {
      printf("%0.4lf ", matrix[i][j]);
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
void createMatrix(double **matrix, int n, int ns)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < ns; j++)
    {
      scanf("%lf", &matrix[i][j]);
    }//for
  }//for

  printf("result matrix\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < ns; j++)
    {
      printf("%f ", matrix[i][j]);
    }//for
    printf("\n");
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
void createRandomMatrix(double **matrix, int n, int ns)
{
  srand48(time(0));
  for (int i = 0; i < n; i++)
  {

    for (int j = 0; j < ns; j++)
    {
        matrix[i][j] = (drand48() * (1000000 - -1000000 + 1)) + -1000000;
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
void initVector(double *vec, int n)
{
  for (int i = 0; i < n; i++)
  {
    vec[i] = 1.0;
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
void printVector(double *vec, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%0.4lf ", vec[i]);
  }//for
  printf("\n");
}//printVector


void Hello(void) {
   int my_rank = omp_get_thread_num();
   int thread_count = omp_get_num_threads();

   printf("Hello from thread %d of %d\n", my_rank, thread_count);

}  /* Hello */

void Forward_elimination(double **matrix, double *vec){

}

void Back_substitution(double **matrix, double *vec){

}

int partial_pivoting(int n, double **matrix){
  double max = fabsf(matrix[0][0]);
  double row = 0;
  // for (int i = 0; i < 1; i++)
  // {

    for (int i = 0; i < n; i++)
    {
      double ij = fabsf(matrix[i][0]);
      if(ij > max){
        max = ij;
        row = i;
      }
    }
    return row;
  // }
}

void swap_rows(){

}

void Gauss_elimination(int n, double **matrix, double *vec){
  int steps = n - 1;

  for (int s = 0; s < 1; s++)
  {
    int max_row = partial_pivoting(n, matrix);
    printf("%d\n", max_row);
    if(max_row != 0){

    }
  }

}


int main(int argc, char* argv[]){
  int n = strtol(argv[1], NULL, 10);
  int thread_count = strtol(argv[2], NULL, 10);

 
// #  pragma omp parallel num_threads(thread_count)
//    Hello();

  int ns = n + 1;
  double *vec = (double *)malloc(sizeof(double *) * n);
  double **matrix = (double **)malloc(sizeof(double *) * n);

  initMatrixVector(matrix, ns);
  
  if (n < 11)
  {
    createMatrix(matrix, n, ns);
  }
  else if (n > 10)
  {
    createRandomMatrix(matrix, n, ns);
  }

  Gauss_elimination(n, matrix, vec);
  // if (n < 11)
  // {
  //   printMatrix(matrix, n);
  //   printVector(vec, n);
  // }
  // initVector(vec, n);
 
  // if (n < 11)
  // {
  //   printMatrix(matrix, n);
  //   printVector(vec, n);
  // }
  return 0;
}