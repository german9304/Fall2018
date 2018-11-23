#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>



int main(void){
    int my_rank, comm_sz;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);



    int numbers[10] = {1,2,3,4,5,6,7,8,9,10};
    int temp[2];
    
    if(my_rank == 0){
    	MPI_Scatter(numbers, 2, MPI_INT, temp, 2, MPI_INT, 0, MPI_COMM_WORLD);
    }else{
    	MPI_Scatter(numbers, 2, MPI_INT, temp, 2, MPI_INT, 0, MPI_COMM_WORLD);
    }


    if(my_rank == 0){
    	printf("rank:%d\n", my_rank);
    	for(int i = 0; i < 2; i++){
            printf("%d ",temp[i]);
    	}
    	printf("\n");
    }else{
    	printf("rank:%d\n", my_rank);
    	for(int i = 0; i < 2; i++){
    		printf("%d ",temp[i]);
    	}
    	printf("\n");
    }

    MPI_Finalize();
	return 0;
}