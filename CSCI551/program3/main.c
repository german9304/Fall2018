/**
 * @file main.c
 * @author  German Razo 
 *
 * @section 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/*
* 
* Tranpose the second matrix from the multiplication,
* this ensures that data is aligned, 
* so the compiler can vectorize it. 
* 
* @param size is the length of the original matrix, 
*  that will get tranpose. 
*
* @param matrix_2 is the matrix that will get tranpose.
*
* @param transpose_matrix matrix will be the result of
* the tranpose of matrix_2. 
*
* @return none 
*/
void isDiagonalDominant(double **matrix, int n)
{
  int count = 0;
  bool greater = false;
  for (int i = 0; i < n; i++)
  {
    double sum = 0.0;
    double diag = 0.0;
    for (int j = 0; j < n; j++)
    {
      if (j != i)
      {
        sum += fabs(matrix[i][j]);
      }
      else
      {
        diag = matrix[i][j];
      } //if
    }   //for
    if (fabs(diag) > fabs(sum))
    {
      greater = true;
    } //if
    if (fabs(diag) >= fabs(sum))
    {
      count++;
    } //if
  }   //for
  if (count == n && greater)
  {
    printf("The system is diagonally dominant\n");
  }
  else
  {
    printf("The system is not diagonally dominant %d %d\n", count, greater);
  } //if
}
/*
* 
* Tranpose the second matrix from the multiplication,
* this ensures that data is aligned, 
* so the compiler can vectorize it. 
* 
* @param size is the length of the original matrix, 
*  that will get tranpose. 
*
* @param matrix_2 is the matrix that will get tranpose.
*
* @param transpose_matrix matrix will be the result of
* the tranpose of matrix_2. 
*
* @return none 
*/
bool absRelApproxErrorJacobi(double *vec, double values[], int n)
{
  double absError[n];
  int count = 0;
  for (int i = 0; i < n; i++)
  {
    absError[i] = fabs((values[i] - vec[i]) / (values[i]));
  }
  for (int i = 0; i < n; i++)
  {
    if (absError[i] < 0.005)
    {
      count++;
    }
  }
  for (int i = 0; i < n; i++)
  {
    vec[i] = values[i];
  }
  return count == n;
}
/*
* 
* Tranpose the second matrix from the multiplication,
* this ensures that data is aligned, 
* so the compiler can vectorize it. 
* 
* @param size is the length of the original matrix, 
*  that will get tranpose. 
*
* @param matrix_2 is the matrix that will get tranpose.
*
* @param transpose_matrix matrix will be the result of
* the tranpose of matrix_2. 
*
* @return none 
*/
bool absRelApproxErrorGauss(double *vec, double values[], int n)
{
  double absError[n];
  for (int i = 0; i < n; i++)
  {
    absError[i] = 0.0;
  }
  int count = 0;
  for (int i = 0; i < n; i++)
  {
    absError[i] = fabs((vec[i] - values[i]) / (vec[i]));
  }
  for (int i = 0; i < n; i++)
  {
    if (absError[i] < 0.005)
    {
      count++;
    }
  }
  for (int i = 0; i < n; i++)
  {
    values[i] = vec[i];
  }
  return count == n;
}
/*
* 
* Tranpose the second matrix from the multiplication,
* this ensures that data is aligned, 
* so the compiler can vectorize it. 
* 
* @param size is the length of the original matrix, 
*  that will get tranpose. 
*
* @param matrix_2 is the matrix that will get tranpose.
*
* @param transpose_matrix matrix will be the result of
* the tranpose of matrix_2. 
*
* @return none 
*/
void JacobiIteration(double **matrix, double *vec, int n, int ns)
{
  printf("Jacobi Iteration\n");
  double sumCur = 0.0;
  double div = 0.0;
  double values[n];
  int iter = 0;
  bool isLess = false;
  while (iter < 100 && !isLess)
  {
    for (int index = 0; index < n; index++)
    {
      values[index] = 0.0;
    }
    for (int i = 0; i < n; i++)
    {
      for (int j = ns - 1; j >= 0; j--)
      {
        if (ns - 1 != j && j != i)
        {
          sumCur += ((-1) * matrix[i][j]) * (vec[j]);
        }//if
        else
        {
          if (ns - 1 == j)
          {
            sumCur = matrix[i][j];
          }
          else if (j == i)
          {
            div = matrix[i][j];
          }
        }//else
      }//for
      values[i] = sumCur / div;
      sumCur = 0.0;
    }//for
    isLess = absRelApproxErrorJacobi(vec, values, n);
    iter++;
  }//while
  if (iter - 1 < 99)
  {
    printf("convergence\n");
    printf("Iterations: %d\n", iter);
  }
  else
  {
    printf("no convergence\n");
  }//else
}

/*
* 
* Tranpose the second matrix from the multiplication,
* this ensures that data is aligned, 
* so the compiler can vectorize it. 
* 
* @param size is the length of the original matrix, 
*  that will get tranpose. 
*
* @param matrix_2 is the matrix that will get tranpose.
*
* @param transpose_matrix matrix will be the result of
* the tranpose of matrix_2. 
*
* @return none 
*/
void GaussSeidel(double **matrix, double *vec, int n, int ns)
{
  printf("Gauss-Seidel iteration\n");
  double sumCur = 0.0;
  double div = 0.0;
  double values[n];
  int iter = 0;
  bool isLess = false;
  while (iter < 100 && !isLess)
  {
    for (int index = 0; index < n; index++)
    {
      values[index] = 0.0;
    }
    for (int i = 0; i < n; i++)
    {
      for (int j = ns - 1; j >= 0; j--)
      {
        if (ns - 1 != j && j != i)
        {
          sumCur += ((-1) * matrix[i][j]) * (vec[j]);
        }
        else
        {
          if (ns - 1 == j)
          {
            sumCur = matrix[i][j];
          }
          else if (j == i)
          {
            div = matrix[i][j];
          }
        }
      }
      double res = sumCur / div;
      values[i] = vec[i];
      vec[i] = res;
      sumCur = 0.0;
      res = 0.0;
    }
    isLess = absRelApproxErrorGauss(vec, values, n);
    iter++;
  }
  if (iter - 1 < 99)
  {
    printf("convergence\n");
    printf("Iterations: %d\n", iter);
  }
  else
  {
    printf("no convergence\n");
  }
}

/*
* 
* Init Matrix and Vector 
* 
* @param matrix , vec, n
*
* @return none 
*
*/
void initMatrixVector(double **matrix, int n)
{
  for (int i = 0; i < n; i++)
  {
    matrix[i] = (double *)malloc(sizeof(double *) * n);
  }
}
/*
* 
* Tranpose the second matrix from the multiplication,
* this ensures that data is aligned, 
* so the compiler can vectorize it. 
* 
* @param size is the length of the original matrix, 
*  that will get tranpose. 
*
* @param matrix_2 is the matrix that will get tranpose.
*
* @param transpose_matrix matrix will be the result of
* the tranpose of matrix_2. 
*
* @return none 
*/
void printMatrix(double **matrix, int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n + 1; j++)
    {
      printf("%0.4lf ", matrix[i][j]);
    }
    printf("\n");
  }
}

/*
* 
* Create Matrix and Vector 
* 
* @param matrix, ns, n
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
    }
  }
}

/*
* 
* Create Random Matrix and Vector 
* 
* @param matrix, ns, n
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
      if (i == j)
      {
        matrix[i][j] = (drand48() * (4000000 - 2000000 + 1)) + 2000000;
      }
      else
      {
        matrix[i][j] = (drand48() * (1000 - (-1000) + 1)) + -1000;
      }
    }
  }
}
/*
* 
* Create Random Matrix and Vector 
* 
* @param matrix, ns, n
*
* @return none 
*
*/
void initVector(double *vec, int n)
{
  for (int i = 0; i < n; i++)
  {
    vec[i] = 1.0;
  }
}
/*
* 
* Tranpose the second matrix from the multiplication,
* this ensures that data is aligned, 
* so the compiler can vectorize it. 
* 
* @param size is the length of the original matrix, 
*  that will get tranpose. 
*
* @param matrix_2 is the matrix that will get tranpose.
*
* @param transpose_matrix matrix will be the result of
* the tranpose of matrix_2. 
*
* @return none 
*/
void printVector(double *vec, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%0.4lf ", vec[i]);
  }
  printf("\n");
}

int main()
{
  int n;
  scanf("%d", &n);
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
  isDiagonalDominant(matrix, n);
  initVector(vec, n);
  JacobiIteration(matrix, vec, n, ns);
  if (n < 11)
  {
    printMatrix(matrix, n);
    printVector(vec, n);
  }
  initVector(vec, n);
  GaussSeidel(matrix, vec, n, ns);
  if (n < 11)
  {
    printMatrix(matrix, n);
    printVector(vec, n);
  }
  return 0;
}
