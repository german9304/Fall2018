#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  

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
    printf("MATRIX_2\n");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            //matrix_2[i][j] = ((float)rand() / RAND_MAX) * (50 + 1 - -50) + -50;
              //matrix_2[i][j] = (float)rand() % (float)(50 + 1 - -50) + -50;
            printf(" %f ",matrix_2[i][j]);
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

int main()
{
    char flag[50];
    scanf("%s",flag);
    int size;
    scanf("%d",&size);
    float matrix_1[size][size];
    float matrix_2[size][size];
    if(!strcmp(flag,"R")){
    	generate_random_matrices(size, matrix_1, matrix_2);
    }else if(!strcmp(flag,"I")){
    	generate_matrices(size,matrix_1, matrix_2);

    }else{
       printf("Invalid flag: %s\n",flag);
    }
	return 0;
}
