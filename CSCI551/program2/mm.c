#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  
#include <sys/time.h>   
#include <sys/resource.h> 

/*
 Multiply matrices 
*/
void multiply(int size, float final_matrix[][size], float matrix_1[][size], float matrix_2[][size]){
    float count = 0.0;
    for(int m = 0; m < size; m++){
        //printf("iter: %d\n",m);
       for(int l = 0; l < size; l++){
       // printf("count: %d\n", l);
        for(int n = 0; n < size; n++){
            count = count + (matrix_1[m][n] * matrix_2[n][l]); 
        }
       // printf(" %.0f ",count);
        final_matrix[m][l] = count;
        count = 0.0;
       }
       //printf("\n");
    }
    //final_matrix[0][0] = 23;
}
/*
 Generates random matrices with numbers [-50,50] 
*/
void generate_random_matrices(int size, float matrix_1[][size], float matrix_2[][size]){

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
void generate_matrices(int size, float matrix_1[][size], float matrix_2[][size]){
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
    getrusage(RUSAGE_SELF, &buf); 
    char flag[50];
    scanf("%s",flag);
    int size;
    scanf("%d",&size);
    float matrix_1[size][size];
    float matrix_2[size][size];
    float final_matrix[size][size];
    if(!strcmp(flag,"R")){
    	generate_random_matrices(size, matrix_1, matrix_2);
    }else if(!strcmp(flag,"I")){
    	generate_matrices(size,matrix_1, matrix_2);

    }else{
       printf("Invalid flag: %s\n",flag);
    }
    #ifdef ALIGNED
    multiply(size,final_matrix, matrix_1, matrix_2);
    print_matrix(size, final_matrix);
    printf("user seconds without microseconds: %ld\n", buf.ru_utime.tv_sec); 
    printf("user microseconds: %ld\n", buf.ru_utime.tv_usec); 
    printf("total user seconds: %e\n", 
       (double) buf.ru_utime.tv_sec 
     + (double) buf.ru_utime.tv_usec / (double) 1000000);

	return 0;
}
