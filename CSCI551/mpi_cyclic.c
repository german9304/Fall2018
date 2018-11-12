#include <stdio.h>
#include <string.h>  /* For strlen             */
#include <mpi.h>     /* For MPI functions, etc */ 
#include <stdlib.h>


//  void mpi_scat(int * arr, int * buff){
//     MPI_Scatter(arr, 2, MPI_INT, buff, 2, MPI_INT, 0, MPI_COMM_WORLD);
// }

int main(void){
	//const int n = 100;
   // char message[n];
    int comm_sz; //number of processes
    int my_rank; //number of ranks
    int n = 12;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    //number of ranks;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int arr[12] = {1,2,3,4,5,6 ,7,8,9,10,11,12};
    int local_n = n/2;
    int temp_store[12/comm_sz];
    int buffTemp[6];
    int iter = 0;
    int * temp = NULL;
    for(int i = local_n; i < n; i++){
      buffTemp[iter] = arr[i];
      iter++;
    }
   int buff[2];
   int res[12];
   int cur = 0;
   for(int i = 0; i < 2; i++){
     if(i%2 == 0){
       temp = arr;
     }else{
      temp = buffTemp;
     }
     MPI_Scatter(temp, 2, MPI_INT, buff, 2, MPI_INT, 0, MPI_COMM_WORLD);
        for(int i = 0; i < 2;i++){
             temp_store[cur] = buff[i];
             cur++;
        }
   }
   MPI_Gather(temp_store , 4, MPI_INT, res, 4, MPI_INT, 0, MPI_COMM_WORLD);
   if(my_rank == 0){
      for(int i = 0; i < 12;i++){
             printf("%d ",res[i]);
      }
      printf("\n");
   }
     
    
    MPI_Finalize();
	return 0;
}