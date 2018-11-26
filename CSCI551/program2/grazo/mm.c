
/**
 * @file mm.c
 * @author  German Razo 
 *
 * @section This program implements matrix multiplication, 
 * and vectorizes the code for better optimization. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  
#include <sys/time.h>   
#include <sys/resource.h> 


/*
* 
* Print user's system, CPU time and maximum resident set size. 
* 
* @param rusage structure 
*
* @return none 
*/
void print_usertime(struct rusage buf){
    printf("---------------------------------------------------\n");
    printf("USER CPU TIME:   %f\n",   (double) buf.ru_utime.tv_sec +  (((double) buf.ru_utime.tv_usec) / (double)1000001));
    printf("USER SYSTEM CPU TIME:   %f\n",   (double) buf.ru_stime.tv_sec +  (((double) buf.ru_stime.tv_usec) / (double)1000001));
    printf("MAXIMUM RESIDENT SET SIZE:  %f\n",   (double) buf.ru_maxrss);
    printf("---------------------------------------------------\n");
}//print_usertime

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
void transpose_matrix(int size, float matrix_2[][size], float transpose_matrix[][size]){
 #pragma novector
   for(int m = 0; m < size; m++){
     #pragma novector
      for(int l = 0;l < size; l++){
           transpose_matrix[m][l] = matrix_2[l][m];
      }//for
    }//for
}//transpose_matrix

/*
* 
* Multiplies two matrices, and tells the compiler that data is aligned 
* with #pragma vector aligned before the third inner loop, 
* and calls the tranpose_matrix function to tranpose matrix_2
* 
* @param size is the length of both matrices
*  that will be multiplied. 
*
* @param matrix_1 first matrix generated that will be multiplied. 
*
* @param matrix_2 second matrix generated that will be multiplied. 
*
* @param final_matrix is the result
* obtained by multiplying matrix_1 and matrix_2. 
*
* @return none 
*/
void multiply(int size, float final_matrix[restrict][size], float matrix_1[restrict][size], float matrix_2[restrict][size], struct rusage buf){

  float t_matrix[size][size] __attribute__((aligned(32)));
  transpose_matrix(size,matrix_2, t_matrix);
    for(int m = 0; m < size; m++){
       for(int l = 0; l < size; l++){
#pragma vector aligned
        for(int n = 0; n < size; n++){
            final_matrix[m][l] += (matrix_1[m][n] * t_matrix[l][n]); 
        }//for
      }//for
    }//for
}//multiply

/*
* 
* Generates two random matrices of type float 
* with numbers in the range [-50, 50]
* 
* @param size is the length of both matrices
*  that will be generated.
*
* @param matrix_1 first matrix that will be generated.
*
* @param matrix_2 second matrix that will be generated. 
*
* @return none 
*/
void generate_random_matrices(int size, float matrix_1[][size], float matrix_2[][size]){
  srand (time(0));
#pragma novector
    for(int i = 0; i < size; i++){
      #pragma novector
        for(int j = 0; j < size; j++){
              matrix_1[i][j] = ((float)rand() / RAND_MAX) * (50 + 1 - -50) + -50;
        }//for
    }//for

#pragma novector
    for(int i = 0; i < size; i++){
      #pragma novector
        for(int j = 0; j < size; j++){
            matrix_2[i][j] = ((float)rand() / RAND_MAX) * (50 + 1 - -50) + -50;
        }//for
    }//for
}//generate_random_matrices

/*
* 
* Generates two random matrices of type float 
* with numbers input by the user. 
* 
* @param size is the length of both matrices
*  that will be generated.
*
* @param matrix_1 first matrix that will be generated.
*
* @param matrix_2 second matrix that will be generated. 
*
* @return none 
*/
void generate_matrices(int size, float matrix_1[][size], float matrix_2[][size]){
  #pragma novector
    for(int i = 0;i < size; i++){
      #pragma novector
       for(int j = 0;j < size; j++){
        scanf("%f",&matrix_1[i][j]);
       }//for
    }//for
  #pragma novector
    for(int i = 0;i < size; i++){
    #pragma novector
       for(int j = 0;j < size; j++){
        scanf("%f",&matrix_2[i][j]);
       }//for
    }//for

}//generate_matrices

/*
* 
* Prints the result obtained by multiplying two matrices. 
* 
* @param size is the length of the result matrix of the multiplication
* of both matrices. 
*
* @return none 
*/
void print_matrix_result(int size, float matrix[][size]){
    float count = 0.0;
    #pragma novector
    for(int m = 0; m < size; m++){
      #pragma novector
       for(int n = 0; n < size; n++){
         printf("%.0f ",matrix[m][n]);
       }
     printf("\n");
    }
}
/*
* 
* Initialize result of the matrix multiplication, 
* called final_matrix 
* 
* @param size is the length of the result matrix of the multiplication
* of both matrices. 
*
* @return none 
*/
void init_matrix(int size, float final_matrix[][size]){
    for(int m = 0; m < size; m++){
      #pragma novector
       for(int n = 0; n < size; n++){
         final_matrix[m][n] = 0.0;
       }
    }
}
int main()
{
    struct rusage buf;  
    char flag[50];
    scanf("%s",flag);
    int size;
    scanf("%d",&size);
    float matrix_1[size][size] __attribute__((aligned(32)));
    float matrix_2[size][size] __attribute__((aligned(32)));
    float final_matrix[size][size]  __attribute__((aligned(32)));
    if(!strcmp(flag,"R")){
    	generate_random_matrices(size, matrix_1, matrix_2);
    }else if(!strcmp(flag,"I")){
    	generate_matrices(size,matrix_1, matrix_2);

    }
    init_matrix(size, final_matrix);
    multiply(size,final_matrix, matrix_1, matrix_2, buf);
    getrusage(RUSAGE_SELF, &buf);
     
    if(!strcmp(flag,"I")){
      print_matrix_result(size, final_matrix);
    }
    print_usertime(buf);

	return 0;
}
