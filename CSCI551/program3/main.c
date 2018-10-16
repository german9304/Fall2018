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
          diag= matrix[i][j];
       }
    }
    // printf("sum: %f  fabs(diag): %f\n",sum, fabs(diag));
    if(fabs(diag) >= fabs(sum)){
       
      count++;
    }
  }
  // printf("before\n");
  // for(int i = 0; i < n; i++){
  //      for(int j = 0; j < n; j++){
  //       printf(" %f ",matrix[i][j]);
  //      }
  //      printf("\n");
  //   }
     // double row1[n];
     // double row2[n];
     // for(int i = 0; i < n;i++){
     //   row1[i] = 0.0;
     //   row2[i] = 0.0;
     // }
     // for(int i = 0; i < n; i++){
     //   for(int j = 0; j < n; j++){
     //      if(i == 0){
     //       row1[j] = matrix[i][j];
     //      }
     //      if(i == n-1){
     //       row2[j]= matrix[i][j];
     //      }
     //   }
       // printf("\n");
    // }
     // printf("\n");
     //   printf("after\n");
      // for(int i = 0; i < n;i++){
      //  matrix[n-1][i] = row1[i];
       // printf(" %f ",row1[i]);
     // }
       // printf("\n");
        // for(int i = 0; i < n;i++){
        //   matrix[0][i] = row2[i];
       // printf(" %f ",row2[i]);
     // }
// for(int i = 0; i < n; i++){
//        for(int j = 0; j < n; j++){
        // printf(" %f ",matrix[i][j]);
       // }
       // printf("\n");
    // }
     // printf("\n");

  if(count == n){
    printf("The system is diagonally dominant\n");
  }else{
    printf("The system is not diagonally dominant\n");
  }
}


bool absRelApproxErrorJacobi(double *vec, double values[], int n){
  double absError[n];
  //  printf("vec: \n");
  // for(int i = 0; i < n; i++){
  //     printf(" %f \n", vec[i]);
  // }
  // printf(" \n");
  // printf("values: \n");
  // for(int i = 0; i < n; i++){
  //     printf("  %f  \n", values[i]);
  // }
  //  printf(" \n");
  int count = 0;
   // printf("\n");
  for(int i = 0; i < n; i++){
    absError[i] = fabs((values[i]-vec[i])/(values[i]));
  }
    // printf("error: \n");
  for(int i = 0; i < n; i++){
      if(absError[i] <= 0.005){
        count++;
      }
        //printf(" %f ", absError[i]);

  }
    // printf("\n");
  // printf("count: %d\n", count);
  if(count != n){
     for(int i = 0; i < n; i++){
      vec[i] = values[i];
     }
   }
  return count == n;
}

bool absRelApproxErrorGauss(double *vec, double values[], int n){
  double absError[n];
  for(int i = 0; i < n; i++){
    absError[i] = 0.0;
  }
  // printf("vec: \n");
  // for(int i = 0; i < n; i++){
  //     printf(" %f \n", vec[i]);
  // }
  // printf(" \n");
  // printf("values: \n");
  // for(int i = 0; i < n; i++){
  //     printf(" %f \n", values[i]);
  // }
  //  printf(" \n");

  int count = 0;
  // printf("\n");
  for(int i = 0; i < n; i++){
    absError[i] = fabs((vec[i]-values[i])/(vec[i]));
  }
   // printf("\n");
  //    printf("error: \n");
  for(int i = 0; i < n; i++){
      if(absError[i] <= 0.005){
          // printf("%d \n", count);
        count++;
      }
           // printf(" %f ", absError[i]);

  }
    // printf("\n");
    // printf("count: %d %d\n", count, n);
  if(count != n){
     // printf("count: %d  %d\n", count, n);
   for(int i = 0; i < n; i++){
    values[i] = vec[i];
   }
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
    // printf("\n");
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
           // printf("\n");
           //  printf(" j:%d  vec:%0.f %0.f ",j, vec[j], matrix[i][j]);
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
  isLess = absRelApproxErrorJacobi(vec, values,n);
  // if(isLess){
  //   printf("true\n");
  // }else{
  //   printf("false\n");
  // }
  //   printf("vector result\n");
  iter++;
 // break;
  // printf("-------------------------------\n");
  }
  // printf("iter: %d\n",iter);
  if(iter-1 < 99){
    printf("convergence\n");
    printf("Iterations: %d\n",iter);
 }else{
  printf("no convergence");
 }
}

void GaussSeidel(double ** matrix,double *vec, int n, int ns){
printf("Gauss-Seidel iteration\n");
  double sumCur = 0.0;
  double div = 0.0;
  double values[n];
  int iter = 0;
  bool isLess = false;
  // printf("vector\n");
  // printf("\n");
    while(iter < 100 && !isLess){
    // printf("-------------------------------\n");
       // printf("iter: %d\n", iter);
    for(int index = 0; index < n; index++){
      values[index] = 0.0;
    }
   for(int i = 0; i < n; i++){
    for(int j = ns - 1; j >= 0; j--){
         if(ns-1!= j && j!=i){
          // printf(" j:%d  vec:%f ",j, vec[j]);
            //printf("before sumCur:%f  ",matrix[i][j]);
            // printf("sum before: %f\n", sumCur);
           
            // printf(" i %d j %d (-1) * %f * %f \n",i, j, vec[j], matrix[i][j]);
            //  printf("\n");
           sumCur+= ((-1)*matrix[i][j])*(vec[j]);
            // printf(" j:%d  vec:%0.f %0.f ",j, vec[j], matrix[i][j]);
           // printf("sum after: %f\n", sumCur);

         }else{
          if(ns-1 == j){
               sumCur = matrix[i][j];
            // printf(" ns-1 == j %d  %0.f ", j, matrix[i][j]);
          }else if(j == i){
             div = matrix[i][j];
             // printf("%f\n",div );
             //printf("after sumCur:%f   %f ",sumCur,  matrix[i][j]);
             // sumCur/= matrix[i][j];
          }
         }
    }
    double res = sumCur/div;
    values[i]=vec[i];
     // printf("\n");
     // printf("i: %d values: %f res: %f\n",i, values[i],  res);
    vec[i] = res;
     // printf("\n");
      // printf("iter: %d\n", i);
  // for(int i = 0; i < n; i++){
  //   printf("%f \n", vec[i]);
  //  }
   // printf("\n");
    sumCur = 0.0;
    res = 0.0;
     // printf("\n");
   }
    // vec[0]=0.0;
   isLess = absRelApproxErrorGauss(vec, values,n);
  // if(isLess){
  //   printf("true\n");
  // }else{
  //   printf("false\n");
  // }
  //   printf("vector result\n");
   iter++;
  // break;
  // printf("-------------------------------\n");
   }
 //  printf("iter: %d\n",iter);
if(iter-1 < 99){
   printf("convergence\n");
   printf("Iterations: %d\n",iter);
 }else{
  printf("no convergence");
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
void initMatrixVector(double **matrix,  int n){
  for(int i = 0; i < n; i++){
  	matrix[i] = (double*)malloc(sizeof(double*)*n);
  }
}

void printMatrix(double **matrix, int n){
   for(int i = 0; i < n; i++){
   	// printf("iter: %d\n",i);
   	for(int j = 0; j < n+1; j++){
   		printf("%0.4lf ",matrix[i][j]);
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
  srand48(time(0));
  for(int i = 0; i < n; i++){

      for(int j = 0; j < ns; j++){
          if(i == j){
            matrix[i][j] = (drand48()) * (4000000 + 1 -2000000) + 2000000;
                // printf(" %d  %d\n", i, j);
          }else{
            matrix[i][j] = (drand48()) * (1000 + 1 - -1000) + -1000;
                // printf(" %f ", matrix[i][j]);
          }
          // printf("\n");
      }
    }
   // printf("matrix\n");
   //  for(int i = 0; i < n; i++){
   //     printf("i: %d  %d\n", i, ns);
   //    for(int j = 0; j < ns; j++){
   //       printf(" %f ", matrix[i][j]);
   //    }
   //     printf("\n");
   //  }

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
 // n = 20;
 //  vec[0] = 1.0;
 //  vec[1] = 0.0;
 //  vec[2] = 1.0;
  // printf("vector print\n");
  // for(int i = 0; i < n; i++){
  //   printf(" %f ",vec[i]);
  // }
  // printf("\n");
  // printf("-------------\n");
}

void printVector(double *vec, int n){
 for(int i = 0; i < n; i++){
    printf("%0.4lf ", vec[i]);
   }
 printf("\n");
}
int main()
{
	int n;
	scanf("%d",&n);
	int ns = n + 1;
  double * vec = (double*)malloc(sizeof(double*) * n);
  double ** matrix = (double**)malloc(sizeof(double*) * n);
  initMatrixVector(matrix, ns);
	if(n < 11){
    createMatrix(matrix,n,ns);
	}else if(n > 10){
    // printf("more than 10\n");
    createRandomMatrix(matrix,n ,ns);
     //printMatrix(matrix, n);
	}
  // printf("\n");
  isDiagonalDominant(matrix,n);
  initVector(vec, n);
  JacobiIteration(matrix, vec, n,ns);
  initVector(vec, n);
  GaussSeidel(matrix, vec, n, ns);
  if(n < 11){
  printMatrix(matrix, n);
  printVector(vec, n);
  }
	return 0;
}




