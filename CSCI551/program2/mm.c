#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  

void generate_random_matrices(int size, int matrix_1[][size], int matrix_2[][size]){

    srand (time(0));
    //int res = 0;
     printf("MATRIX_1 \n");
    for(int i = 0; i < size; i++){
        printf("Iteration: %d\n",i);
        for(int j = 0; j < size; j++){
              matrix_1[i][j] = rand() % (50 + 1 - -50) + -50;
            //res = rand() % (50 + 1 - -50) + -50;
            printf(" %d ",matrix_1[i][j]);
        }
        printf("\n");
    }
    printf("MATRIX_2 \n");
    for(int i = 0; i < size; i++){
        printf("Iteration: %d\n",i);
        for(int j = 0; j < size; j++){
              matrix_2[i][j] = rand() % (50 + 1 - -50) + -50;
             //res = rand() % (50 + 1 - -50) + -50;
             printf(" %d ",matrix_2[i][j] );
        }
        printf("\n");
    }

 //matrix[0][0] = 1;
    /*
     printf("matrix_1: \n");
    for(int i = 0;i < size; i++){
        for(int j = 0;j < size; j++){
            printf("%d",matrix_1[i][j]);
        }
        printf("\n");
    }
     printf("matrix_2: \n");
    for(int i = 0;i < size; i++){
        for(int j = 0;j < size; j++){
            printf("%d",matrix_2[i][j]);
        }
        printf("\n");
    }
    */
}
void generate_matrices(int size, int matrix_1[][size], int matrix_2[][size]){
    for(int i = 0;i < size; i++){
       for(int j = 0;j < size; j++){
        scanf("%d",&matrix_1[i][j]);
       }
    }
    for(int i = 0;i < size; i++){
       for(int j = 0;j < size; j++){
        scanf("%d",&matrix_2[i][j]);
       }
    }
    printf("matrix_1: \n");
    for(int i = 0;i < size; i++){
        for(int j = 0;j < size; j++){
            printf("%d",matrix_1[i][j]);
        }
        printf("\n");
    }
     printf("matrix_2: \n");
    for(int i = 0;i < size; i++){
        for(int j = 0;j < size; j++){
            printf("%d",matrix_2[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    char flag[50];
    scanf("%s",flag);
    int size;
    scanf("%d",&size);
    int matrix_1[size][size];
    int matrix_2[size][size];
    if(!strcmp(flag,"R")){
    	generate_random_matrices(size, matrix_1, matrix_2);
    }else if(!strcmp(flag,"I")){
    	generate_matrices(size,matrix_1, matrix_2);

    }else{
       printf("Invalid flag: %s\n",flag);
    }

	return 0;
}
