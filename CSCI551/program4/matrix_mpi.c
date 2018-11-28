#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

void getUserInput(int *n, char form[], char flag[], int rank)
{
    if (rank == 0)
    {
        scanf("%s", form);
        scanf("%s", flag);
        scanf("%d", n);
        // printf("testing %s, %s, %d\n", form, flag, n);
    }
    MPI_Bcast(form, 3, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(flag, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(n, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

/**
 * @brief 
 * 
 * @param n 
 * @param matrix_1 
 * @param matrix_2 
 */
void readMatrix1(
    int n,
    int comm_sz,
    int p_r,
    int my_rank, 
    double global_m[],
    double matrix_1[][n],
    int send_counts[],
    int displs[n])
{

    if (my_rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //printf("j: %d\n", j);
                scanf("%lf", &matrix_1[i][j]);
            }
        } //for


    }

    if(my_rank == 0){
        int sum = 0;
        printf("sendcounts\n");
        for(int i = 0; i < comm_sz; i++){
           printf("%d ", send_counts[i]);
        }
        for(int i = 0; i < comm_sz; i++){
            displs[i] = sum;
            sum += send_counts[i];
        }
        printf("\n");
        MPI_Scatterv(matrix_1, send_counts, displs, MPI_DOUBLE, 
             global_m, p_r, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }else{
        MPI_Scatterv(matrix_1, send_counts, displs, MPI_DOUBLE, 
             global_m, p_r, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }


}


int main(void){

    char form[50];
    char flag[50];

    int my_rank, comm_sz, div, n;
    int p1, c1, p2, r_m, p_r;
    int sum  = 0;
    int total;
    int total_sum = 0;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    getUserInput(&n, form, flag, my_rank);

    total = n * n;
    double matrix_1[n][n];
    int send_counts[comm_sz];
    int displs[comm_sz];
    for(int i = 0; i < comm_sz; i++){
        send_counts[i] = 0;
        displs[i] = 0;
    }
    // MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&total, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double global_m[n * n];
    // for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            global_m[j] = 0;
        }
    // }

    r_m = n % comm_sz; //reminder
    p_r = n / comm_sz;

    if(my_rank == 0){
        if(r_m != 0){
           p_r = p_r + 1;
        }
        p_r *= n;
        MPI_Gather(&p_r, 1, MPI_INT, send_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }else{
        int sub = r_m - 1;
        if(r_m > 0 && my_rank < r_m){
            p_r+=1;
        }
        p_r *= n;
        MPI_Gather(&p_r, 1, MPI_INT, send_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    MPI_Reduce(&p_r, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


    if (!strcmp(flag, "R"))
    {
        printf("random\n");

        // randomMatrix(n, matrix_1, matrix_2);
    }
    else if (!strcmp(flag, "I"))
    {
        // printf("read matrix I\n");
        readMatrix1(n, comm_sz, p_r, my_rank, global_m, 
            matrix_1, send_counts, displs);

        // readMatrix2();
    }
    else
    {
        printf("error command I\n");
    }




    

    if(my_rank == 0){
      printf("total_sum:%d\n", total_sum);
    }
        for (int i = 0; i < p_r/n; ++i)
        {
            for(int k = 0; k < n; k++){
               int ind = (i * n + k);
                   printf("%f ",global_m[ind]);
            }
            printf("\n");
            /* code */
        }
    // }


    MPI_Finalize();
	return 0;
}

