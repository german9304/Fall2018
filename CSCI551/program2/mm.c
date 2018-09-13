#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void random_matrices(int size){
 printf("size: %d\n",size);
}
void matrices(int size, int arr[][size]){
	 for(int i = 0;i < size; i++){
			for(int j = 0;j < size; j++){
				scanf("%d",&arr[i][j]);
			}
		}
}


int main(int argc, char const *argv[])
{
    char flag[50];
    scanf("%s",flag);
    if(!strcmp(flag,"R")){
    	int size;
    	scanf("%d",&size);
    	random_matrices(size);
    }else if(!strcmp(flag,"I")){
    	int size;
    	scanf("%d",&size);
    	printf("size: %d\n",size);
    	int m = size;
    	int n = size;
    	int matrix_1[m][n];
    	matrices(size,matrix_1);
    	printf("matrix: \n");
    	for(int i = 0;i < size; i++){
    		for(int j = 0;j < size; j++){
    			printf("%d",matrix_1[i][j]);
    		}
    		printf("\n");
    	}

    }else{
       //printf("Flag else type: %s\n",flag);
    }

	return 0;
}