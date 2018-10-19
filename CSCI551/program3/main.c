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
* Tests if the matrix is diagonal dominant.
* 
* @param n size of the matrix to be tested.
*
* @param matrix is the matrix that will be tested if
*       it has diagonal dominant.
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
    printf("The system is not diagonally dominant\n");
  } //else
}//isDiagonalDominant

/*
* 
* Calculates if the absolute relative approximate error 
*   from Jacobi Iteration method is less than 0.005. 
*   After the ith iteration from Jacobi method the vector vec and values 
*   contain the new and old numbers to calulcate the (ARAE). 
* 
* @param n size of the matrix.
*
* @param vec is the vector that contains the previous numbers
*        obtained by running the ith iteration from Jacobi Iteration method, 
*        so these numbers get compared with 0.005. 
*
* @param values is an array of doubles that contains the starting approximation 1's 
*        and the new values obtained by running the ith iteration 
*        from Jacobi Iteration method. 
*
* @return boolean if ARAE is less than 0.005 return true, 
*         otherwise return false. 
*/

bool absRelApproxErrorJacobi(double *vec, double values[], int n)
{
  double absError[n];
  int count = 0;
  for (int i = 0; i < n; i++)
  {
    absError[i] = fabs((values[i] - vec[i]) / (values[i]));
  }//for
  for (int i = 0; i < n; i++)
  {
    if (absError[i] < 0.005)
    {
      count++;
    }
  }//for
  for (int i = 0; i < n; i++)
  {
    vec[i] = values[i];
  }//for
  return count == n;
}//absRelApproxErrorJacobi

/*
* 
* Calculates if the absolute relative approximate error 
*   from Gauss-Seidel Iteration method is less than 0.005. 
*   After the ith iteration from Gauss-Seidel method the vector vec and values 
*   contain the new and old numbers to calulcate the (ARAE). 
* 
* @param n size of the matrix.
*
*
* @param values is an array of doubles that contains the starting approximation 1's
*        and the new values obtained by running the ith iteration
*        from Gauss-Seidel Iteration method.
*
*
* @param vec is the vector that contains the previous numbers
*        obtained by running the ith iteration from Gauss-Seidel Iteration method. 
*        so these numbers get compared with 0.005. 
*
* @return boolean if ARAE is less than 0.005 return true, 
*         otherwise return false. 
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
}//absRelApproxErrorGauss

/*
* 
* Calculates the Jacobi Iteration method,
* on the given matrix. 
* 
* @param matrix is the matrix where Jacobi Iteration method
*        will be calculated
*
* @param vec is the matrix that will get tranpose.
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
}//JacobiIteration

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
    }//for
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
          }//else if
        }//else
      }//for
      double res = sumCur / div;
      values[i] = vec[i];
      vec[i] = res;
      sumCur = 0.0;
      res = 0.0;
    }//for
    isLess = absRelApproxErrorGauss(vec, values, n);
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
  }//for
}//initMatrixVector
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
    }//for
    printf("\n");
  }//for
}//printMatrix

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
void createMatrix(double **matrix, int n, int ns)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < ns; j++)
    {
      scanf("%lf", &matrix[i][j]);
    }//for
  }//for
}//createMatrix

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
      }//else
    }//for
  }//for
}//createRandomMatrix
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
void initVector(double *vec, int n)
{
  for (int i = 0; i < n; i++)
  {
    vec[i] = 1.0;
  }//for
}//initVector
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
  }//for
  printf("\n");
}//printVector

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
