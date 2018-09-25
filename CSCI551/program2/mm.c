#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  
#include <sys/time.h>   
#include <sys/resource.h> 
// #include <immintrin.h>



void transpose_matrix(int size, float matrix_2[restrict][size], float transpose_matrix[restrict][size]){
   for(int m = 0; m < size; m++){
      for(int l = 0;l < size; l++){
        // for(int j = 0; j < size; j++){
           transpose_matrix[m][l] = matrix_2[l][m];
        // }
      }
    }
}
/*
 Multiply matrices  
*/
void multiply(int size, float final_matrix[restrict][size], float matrix_1[restrict][size], float matrix_2[restrict][size]){
    // float count = 0.0;
  float t_matrix[size][size] __attribute__((aligned(32)));
  transpose_matrix(size,matrix_2, t_matrix);
  //    printf("transpose_matrix: \n");
  // for(int m = 0; m < size; m++){
  //     for(int l = 0;l < size; l++){
  //        printf("%.0f ",t_matrix[m][l]);
  //     }
  //     printf("\n");
  // }

    for(int m = 0; m < size; m++){
        //printf("iter: %d\n",m);
       for(int l = 0; l < size; l++){
       // printf("count: %d\n", l);
#pragma vector aligned
        for(int n = 0; n < size; n++){
            final_matrix[m][l] +=  (matrix_1[m][n] * t_matrix[m][n]); 
        }
       // printf(" %.0f ",count);
        // final_matrix[m][l] = count;
        // count = 0.0;
       }
       //printf("\n");
    }
    //final_matrix[0][0] = 23;
}
/*
 Generates random matrices with numbers [-50,50] 
*/
void generate_random_matrices(int size, float matrix_1[restrict][size], float matrix_2[restrict][size]){

    srand (time(0));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
              matrix_1[i][j] = ((float)rand() / RAND_MAX) * (50 + 1 - -50) + -50;
        }
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            matrix_2[i][j] = ((float)rand() / RAND_MAX) * (50 + 1 - -50) + -50;
              //matrix_2[i][j] = (float)rand() % (float)(50 + 1 - -50) + -50;
        }
    }
    /*
     printf("MATRIX_1\n");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            //matrix_2[i][j] = ((float)rand() / RAND_MAX) * (50 + 1 - -50) + -50;
              //matrix_2[i][j] = (float)rand() % (float)(50 + 1 - -50) + -50;
            printf(" %.0f ",matrix_1[i][j]);
        }
        printf("\n");
    }

    printf("MATRIX_2\n");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            //matrix_2[i][j] = ((float)rand() / RAND_MAX) * (50 + 1 - -50) + -50;
              //matrix_2[i][j] = (float)rand() % (float)(50 + 1 - -50) + -50;
            printf(" %.0f ",matrix_2[i][j]);
        }
        printf("\n");
    }
   */

}

/*
 Generates matrices with numbers from user input
*/
void generate_matrices(int size, float matrix_1[restrict][size], float matrix_2[restrict][size]){
    for(int i = 0;i < size; i++){
       for(int j = 0;j < size; j++){
        scanf("%f",&matrix_1[i][j]);
       }
    }
    for(int i = 0;i < size; i++){
       for(int j = 0;j < size; j++){
        scanf("%f",&matrix_2[i][j]);
       }
    }
}

void print_matrix(int size, float matrix[][size]){
    float count = 0.0;
    for(int m = 0; m < size; m++){
        //printf("iter: %d\n",m);
       for(int n = 0; n < size; n++){
         printf("%.0f ",matrix[m][n]);
       }
     printf("\n");
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


    // float   matrix_2[size][size] __attribute__((aligned(32)));
    // float  final_matrix[size][size] __attribute__((aligned(32))); 
    //  float matrix_1[size][size];
    // float   matrix_2[size][size];
    // float  final_matrix[size][size];
    if(!strcmp(flag,"R")){
    	generate_random_matrices(size, matrix_1, matrix_2);
    }else if(!strcmp(flag,"I")){
    	generate_matrices(size,matrix_1, matrix_2);

    }else{
       printf("Invalid flag: %s\n",flag);
    }
    multiply(size,final_matrix, matrix_1, matrix_2);
    //multiplyVec(size, matrix_1, matrix_2);
    getrusage(RUSAGE_SELF, &buf);
    if(!strcmp(flag,"I")){
    print_matrix(size, final_matrix);
     }
    printf("user seconds without microseconds: %ld\n", buf.ru_utime.tv_sec); 
    printf("user microseconds: %ld\n", buf.ru_utime.tv_usec); 
    printf("USER CPU TIME: %e\n",  (double) buf.ru_utime.tv_sec + (double) buf.ru_utime.tv_usec / (double) 1000001);
    printf("USER SYSTEM CPU TIME: %e\n",  (double) buf.ru_stime.tv_sec + (double) buf.ru_stime.tv_usec / (double) 1000001);
    printf("MAXIMUM RESIDENT SET SIZE: %e\n",  (double) buf.ru_maxrss);

	return 0;
}
