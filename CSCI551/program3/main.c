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


void isDiagonalDominant(double ** matrix, int n){
  int count = 0;
  for(int i = 0; i < n; i++){
    double sum = 0.0;
    double diag = 0.0;
    for(int j = 0; j < n; j++){
       if(j!= i){
          sum+= matrix[i][j];
       }else{
          diag = matrix[i][j];
       }
    }
    if(fabs(diag) > sum){
      // printf("sum: %f\n",sum);
      count++;
    }
  }
  if(count == n){
    printf("the system is diagonally dominant\n");
  }else{
    printf("the system is not diagonally dominant\n");
  }
}


bool absRelApproxError(double *vec, double values[], int n){
  double absError[n];
  // printf("vec: \n");
  // for(int i = 0; i < n; i++){
  //     printf(" %f ", vec[i]);
  // }
  // printf(" \n");
  // printf("values: \n");
  // for(int i = 0; i < n; i++){
  //     printf(" %f ", values[i]);
  // }
  int count = 0;
  for(int i = 0; i < n; i++){
    absError[i] = (values[i]-vec[i])/(values[i]);
  }
   // printf("error: \n");
  for(int i = 0; i < n; i++){
      if(absError[i] < 0.005){
        count++;
      }
       // printf(" %f ", absError[i]);

  }
  // printf("\n");
  // printf("count: %d\n", count);
   for(int i = 0; i < n; i++){
    vec[i] = values[i];
   }
  return count == n;
}
void JacobiIteration(double ** matrix,double *vec, int n, int ns){
  printf("Jacobi Iteration\n");
    double sumCur = 0.0;
    double div = 0.0;
    double values[n];
    int iter = 0;
     bool isLess = false;
  while(iter < 100 && !isLess){
    // printf("-------------------------------\n");
    // printf("iter: %d\n", iter);
    for(int index = 0; index < n; index++){
      values[index] = 0.0;
    }
   for(int i = 0; i < n; i++){
    // printf("Iter: %d \n", i);
    for(int j = ns - 1; j >= 0; j--){
         if(ns-1!= j && j!=i){
          // printf("before sumCur:%f   %f ",sumCur,  matrix[i][j]);
           sumCur+= ((-1)*matrix[i][j])*(vec[j]);
           // printf(" j:%d  vec:%0.f %0.f ",j, vec[j], matrix[i][j]);
         }else{
          if(ns-1 == j){
               sumCur = matrix[i][j];
            // printf(" ns-1 == j %d  %0.f ", j, matrix[i][j]);
          }else if(j == i){
             div = matrix[i][j];
             // printf("after sumCur:%f   %f ",sumCur,  matrix[i][j]);
             // sumCur/= matrix[i][j];
          }
         }
    }
    values[i]=sumCur/div;
     // printf(" %f ", sumCur/div);
    sumCur = 0.0;
    // printf("\n");
   }
    // vec[0]=0.0;
  isLess = absRelApproxError(vec, values,n);
  // if(isLess){
  //   printf("true\n");
  // }else{
  //   printf("false\n");
  // }
  //   printf("vector result\n");
  iter++;
  // printf("-------------------------------\n");
  }
  printf("iter: %d\n",iter);
  if(iter-1 < 99){
  for(int i = 0; i < n; i++){
    printf("%0.4f ", vec[i]);
   }
 }else{
  printf("no convergence");
 }
 printf("\n");
}

void GaussSeidel(){

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
void initMatrixVector(double **matrix,  int n){
  for(int i = 0; i < n; i++){
  	matrix[i] = (double*)malloc(sizeof(double*)*n);
  }
}

void printMatrix(double **matrix, int n){
   for(int i = 0; i < n; i++){
   	printf("iter: %d\n",i);
   	for(int j = 0; j < n+1; j++){
   		printf(" %lf ",matrix[i][j]);
   	}
   	printf("\n");
   	printf("---------------------- \n");
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

void createMatrix(double ** matrix, int n, int ns){
  for(int i = 0; i < n; i++){
    	for(int j = 0; j < ns; j++){
          scanf("%lf",&matrix[i][j]);
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
void createRandomMatrix(double ** matrix, int n, int ns){
  srand48(time(NULL));
  for(int i = 0; i < n; i++){
      for(int j = 0; j < ns; j++){
          matrix[i][j] = (drand48()) * (4.000000 + 1 - -2.000000) + -2.000000;
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
void initVector(double *vec,int n){
  for(int i = 0; i < n; i++){
    vec[i] = 1.0;
  }
  // printf("vector print\n");
  // for(int i = 0; i < n; i++){
  //   printf(" %f ",vec[i]);
  // }
  // printf("\n");
  // printf("-------------\n");
}

int main()
{
	int n;
	scanf("%d",&n);
	int ns = n + 1;
  double * vec = (double*)malloc(sizeof(double*) * n);
  double ** matrix = (double**)malloc(sizeof(double*) * n);
  initVector(vec, n);
  initMatrixVector(matrix, ns);
	if(n < 11){
    createMatrix(matrix,n,ns);
    // printMatrix(matrix, n);
	}else if(n > 10){
    createRandomMatrix(matrix,n ,ns);
    // printMatrix(matrix, n);
	}
  isDiagonalDominant(matrix,n);
  JacobiIteration(matrix, vec, n,ns);



	return 0;
}




