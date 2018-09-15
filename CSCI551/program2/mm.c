#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  

void random_matrices(int size, int matrix[][size]){
 //int iSecret, iGuess;
    printf("size: %d\n",size);
 //matrix[0][0] = 1;
    for(int i =0; i < size; i++){
        for(int j = 0; j< size; j++){
            matrix[i][j] = j;
        }
    }
    printf("GENERATED MATRIX: \n");
     for(int i =0; i < size; i++){
        for(int j = 0; j< size; j++){
            printf("%d\n",matrix[i][j]);
        }
    }

}
void matrices(int size, int matrix[][size]){
    for(int i = 0;i < size; i++){
       for(int j = 0;j < size; j++){
        scanf("%d",&matrix[i][j]);
       }
    }
    printf("matrix: \n");
    for(int i = 0;i < size; i++){
        for(int j = 0;j < size; j++){
            printf("%d",matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    char flag[50];
    scanf("%s",flag);
    if(!strcmp(flag,"R")){
        int size;
    	scanf("%d",&size);
        int matrix[size][size];
        //printf("row col %d\n",matrix[0][0]);
        printf("size: %d\n",size );
    	random_matrices(size, matrix);
    }else if(!strcmp(flag,"I")){
    	int size = 0;
    	scanf("%d",&size);
    	printf("size: %d\n",size);
    	int matrix_1[size][size];
    	matrices(size,matrix_1);

    }else{
       //printf("Flag else type: %s\n",flag);
    }

	return 0;
}
