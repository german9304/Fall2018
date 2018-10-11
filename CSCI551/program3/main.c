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

void absRelApproxError(){

}
void JacobiIteration(){

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

int main()
{
	int n;
	scanf("%d",&n);
	int ns = n + 1;
    double ** matrix = (double**)malloc(sizeof(double*) * n);
    initMatrixVector(matrix, ns);
	if(n < 11){
    createMatrix(matrix,n,ns);
    printMatrix(matrix, n);
	}else if(n > 10){
       
	}
	return 0;
}