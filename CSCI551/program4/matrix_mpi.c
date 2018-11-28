#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>



int main(void){
    int my_rank, comm_sz, div, n;
    int p1, c1, p2, r_m, p_r;
    int sum  = 0;
    int total;
    int total_sum = 0;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank == 0){
        scanf("%d", &n);
        printf("%d\n",n);
        total = n * n;
    }
    int sendCounts[comm_sz];
    int displs[comm_sz];
    for(int i = 0; i < comm_sz; i++){
        sendCounts[i] = 0;
        displs[i] = 0;;
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&total, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int global_m[n * n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            global_m[i] = 0;
        }
    }
    int numbers[16] = {
        5,2,3,4, 
        1,2,3,2,  
        5,100,3,45,  
        4,4,3,4};
    // int temp[10];
    r_m = n % comm_sz; //reminder
    p_r = n / comm_sz;
  
    // int r_p = remind * n;  //row per processor
    // int r_m = (n * n) - (r_p * (comm_sz - 1));
    
    if(my_rank == 0){
        if(r_m != 0){
           p_r = p_r + 1;
        }
        // printf("remind:%d, div:%d \n", r_m, div);
        // printf("rank:%d, p_r:%d\n", my_rank, p_r);
        // sendCounts[my_rank] = p_r;
        p_r *= n;
        MPI_Gather(&p_r, 1, MPI_INT, sendCounts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }else{
        int sub = r_m - 1;
        if(r_m > 0 && my_rank < r_m){
            p_r+=1;
           // printf("rank:%d, p_r:%d \n", my_rank, p_r);
        }/*else{
            // printf("rank:%d, p_r:%d\n", my_rank, p_r);
        }*/
        // from = my_rank * p_r/comm_sz;
        // to = (my_rank+1) * p_r/comm_sz;
        p_r *= n;
        // sendCounts[my_rank] = p_r;
        MPI_Gather(&p_r, 1, MPI_INT, sendCounts, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // printf("rank:%d, p_r:%d\n", my_rank, p_r);
    }
    MPI_Reduce(&p_r, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    // div = n / comm_sz;
    // int sendCounts[comm_sz];
    // int dpls[comm_sz];
    // for(int i = 0; i < comm_sz; i++){
    //     dpls[i] = 0;
    // }
    // c1 = 10;
    // pr = 5;
    
    // sendCounts[0] = c1;
    // dpls[0] = 0;
    // // sum  = dpls[0];

    // for(int i = 1; i < comm_sz; i++){
    //    //  printf("sum: %d\n", sum);
    //     sendCounts[i] = pr;
    //     dpls[i] = sum;
    //     // printf("rank:%d, dpls:%d\n", my_rank,dpls[i]);
    //     sum+= sendCounts[i];
    //  }
    // int sendCounts[3] = {1,1,2};
    // for(int j = 0; j < comm_sz; j++){
    //  dpls[j] = j;
    //  printf("rank:%d, dpls:%d\n", my_rank, dpls[j]);
    // }
    // int temp[10];
    // for(int i = 0; i < pr; i++){
    //     temp[i] = 0;
    // }
    // // printf("c1: %d, pr:%d\n", c1, pr);
    // if(my_rank == 0){
    // 	MPI_Scatterv(numbers, sendCounts, dpls, MPI_INT, 
    //         temp, 10, MPI_INT, 0, MPI_COMM_WORLD);
    // }else{
    // 	MPI_Scatterv(numbers, sendCounts, dpls, MPI_INT, 
    //         temp, 5, MPI_INT, 0, MPI_COMM_WORLD);
    // }
    // if(my_rank == 0){
    //  c1 = 5;
    //  MPI_Scatter(numbers, c1, MPI_INT, temp, 10, MPI_INT, 0, MPI_COMM_WORLD);
    // }else{
    //     c1 = 10;
    //  MPI_Scatter(numbers, c1, MPI_INT, temp, 10, MPI_INT, 0, MPI_COMM_WORLD);
    // }


    if(my_rank == 0){
        printf("sendcounts\n");
        for(int i = 0; i < comm_sz; i++){
           printf("%d ", sendCounts[i]);
        }
    	for(int i = 0; i < comm_sz; i++){
            displs[i] = sum;
            sum += sendCounts[i];
           // printf("%d ",sendCounts[i]);
        }
        // printf("\n");
        // printf("displacements\n");
        // for(int i = 0; i < comm_sz; i++){
        //     printf("%d ",displs[i]);
        // }
        printf("\n");
        // printf("my_rank:%d, from:%d, to:%d\n", my_rank, from, to);
        // printf("rank:%d, total_sum:%d p_r:%d\n", my_rank, total_sum, p_r);
        MPI_Scatterv(numbers, sendCounts, displs, MPI_INT, 
             global_m, p_r, MPI_INT, 0, MPI_COMM_WORLD);
    }else{
        printf("\n");
        // printf("my_rank:%d, from:%d, to:%d\n", my_rank, from, to);
        MPI_Scatterv(numbers, sendCounts, displs, MPI_INT, 
             global_m, p_r, MPI_INT, 0, MPI_COMM_WORLD);
        // printf("rank:%d, total_sum:%d p_r:%d\n", my_rank, total_sum, p_r);
    }
    // 	printf("\n");
    // }else{
    // 	// printf("rank:%d\n", my_rank);
     // if(my_rank == 0){
       //  printf("global_m\n");
    	 // for(int i = 0; i < n; i++){
    		// for(int j = 0; j < n; j++){
    // int from = my_rank * p_r/n;
    // int to = (my_rank+1) * p_r/n;
    // printf("my_rank:%d, n:%d \n", my_rank, p_r/n);
    // MPI_Barrier(MPI_COMM_WORLD);
    if(my_rank == 0){
        for (int i = 0; i < p_r/n; ++i)
        {
            for(int k = 0; k < n; k++){
                int ind = (i * n + k);
                    printf("%d ",global_m[ind]);
            }
            printf("\n");
            /* code */
        }
    }
            // }
        // }
             // printf("\n");
     // }
    // }
    // 	printf("\n");
    // }

    MPI_Finalize();
	return 0;
}



// #include <mpi.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// #define SIZE 4

// int main(int argc, char *argv[])
// {
//     int rank, size;     // for storing this process' rank, and the number of processes
//     int *sendcounts;    // array describing how many elements to send to each process
//     int *displs;        // array describing the displacements where each segment begins

//      // elements remaining after division among processes
//     int sum = 0;                // Sum of counts. Used to calculate displacements
//     char rec_buf[100];          // buffer where the received data should be stored

//     // the data to be distributed
//     char data[SIZE][SIZE] = {
//         {'a', 'b', 'c', 'd'},
//         {'e', 'f', 'g', 'h'},
//         {'i', 'j', 'k', 'l'},
//         {'m', 'n', 'o', 'p'}
//     };

//     MPI_Init(&argc, &argv);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);

//     sendcounts = malloc(sizeof(int)*size);
//     displs = malloc(sizeof(int)*size);

//     int rem = (SIZE*SIZE)%size;

//     // calculate send counts and displacements
//     // for (int i = 0; i < size; i++) {
//     //     sendcounts[i] = (SIZE*SIZE)/size;
//     //     if (rem > 0) {
//     //         sendcounts[i]++;
//     //         rem--;
//     //     }

//     //     displs[i] = sum;
//     //     sum += sendcounts[i];
//     // }
//     int sc = (SIZE*SIZE)/size;
//     int res = sec - rem;

//     if(rank == 0){

//     }

//     // print calculated send counts and displacements for each process
//     if (0 == rank) {
//         for (int i = 0; i < size; i++) {
//             printf("sendcounts[%d] = %d\tdispls[%d] = %d\n", i, sendcounts[i], i, displs[i]);
//         }
//     }

//     // divide the data among processes as described by sendcounts and displs
//     MPI_Scatterv(&data, sendcounts, displs, MPI_CHAR, &rec_buf, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

//     // print what each process received
//     printf("%d: ", rank);
//     for (int i = 0; i < sendcounts[rank]; i++) {
//         printf("%c\t", rec_buf[i]);
//     }
//     printf("\n");

//     MPI_Finalize();

//     free(sendcounts);
//     free(displs);

//     return 0;
// }