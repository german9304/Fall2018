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

void absRelApproxError(){

}
void JacobiIteration(double ** matrix,double *vec, int n, int ns){
  printf("JacobiIteration\n");
    double sumCur = 0.0;
    double div = 0.0;
    double values[n];
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
   printf("vector result\n");
   for(int i = 0; i < n; i++){
    vec[i] = values[i];
    printf("vec: %f ", vec[i]);
   }
   printf("\n");
}

void GaussSeidel(){

} 

bool isDiagonalDominant(){
	return false;
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
    printMatrix(matrix, n);
	}else if(n > 10){
    createRandomMatrix(matrix,n ,ns);
    printMatrix(matrix, n);
	}
  JacobiIteration(matrix, vec, n,ns);



	return 0;
}




