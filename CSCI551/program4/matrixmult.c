#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>      
#include <mpi.h>



void transpose_matrix(
    int n,
    int **m_2,
    int **t_m)
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            t_m[i][j] = m_2[j][i];
        } //for
    }     //for
} //transpose_matrix



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
void input_matrix(
    int n,
    int my_rank, 
    int *matrix_1,
    int *matrix_2)
{

    if (my_rank == 0)
    {
        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         //printf("j: %d\n", j);
        //         scanf("%d", &matrix_1[i][j]);
        //     }
        // } //for
        for (int i = 0; i < n * n; i++)
        {
                //printf("j: %d\n", j);
                scanf("%d", &matrix_1[i]);
        } //for

        for (int i = 0; i < n * n; i++)
        {
           
                scanf("%d", &matrix_2[i]);
        } //for
        // for (int i = 0; i < n * n; ++i)
        // {
        //     scanf("%d", &matrix_1[i]);
        // }
        //  for (int i = 0; i < n * n; ++i)
        // {
        //     scanf("%d", &matrix_2[i]);
        // }
    }

    // if(my_rank == 0){
    //     int sum = 0;
    //     for(int i = 0; i < comm_sz; i++){
    //         displs[i] = sum;
    //         sum += send_counts[i];
    //     }
    // }
    // if (!strcmp(form, "kij"))
    // {
    //     transpose_matrix(n, matrix_1, t_m);
    //     MPI_Scatterv(t_m, send_counts, displs, MPI_DOUBLE, 
    //     local_m, p_r, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // }else{
    //     MPI_Scatterv(matrix_1, send_counts, displs, MPI_DOUBLE, 
    //     local_m, p_r, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // }

    // MPI_Bcast(matrix_2, n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}



/**
 * @brief 
 * 
 * @param n 
 * @param matrix_1 
 * @param matrix_2 
 */
void random_matrix(
    int n,
    int my_rank, 
    int *matrix_1,
    int *matrix_2)
{
    srand (time(0));

    if (my_rank == 0)
    {
        for (int i = 0; i < n * n; i++)
        {
                matrix_1[i] = rand() % 100;
        } //for

        for (int i = 0; i < n * n; i++)
        {
            matrix_2[i] = rand() % 100;
        } //for
    }
}

void scatter_matrix(
    int n, 
    int comm_sz,
    int p_r,
    int my_rank, 
    int *local_m,
    int *matrix_1,
    int *matrix_2,
    int *send_counts,
    int *displs){

    if(my_rank == 0){
        int sum = 0;
        for(int i = 0; i < comm_sz; i++){
            displs[i] = sum;
            sum += send_counts[i];
        }
    }
        MPI_Scatterv(matrix_1, send_counts, displs, MPI_INT, 
        local_m, p_r, MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Bcast(matrix_2, n * n, MPI_INT, 0, MPI_COMM_WORLD);
}



/**
 * @brief 
 * 
 * @param n 
 * @param matrix_1 
 * @param matrix_2 
 */
void ijkForm(
    int n,
    int p_r,
    int *m_1,
    int *m_2,
    int *r_m)
{

    for (int i = 0; i < p_r/n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                r_m[i * n + j] += m_1[i * n + k] * m_2[k * n + j];
            }
        }
    }
    
}
/**
 * @brief 
 * 
 * @param n 
 * @param matrix_1 
 * @param matrix_2 
 */
void ikjForm(
    int n,
    int p_r,
    int *m_1,
    int *m_2,
    int *r_m)
{
    for (int i = 0; i < p_r/n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            for (int j = 0; j < n; j++)
            {
                r_m[i * n + j] += m_1[(i * n) + k] * m_2[k * n + j];
            }
        }
    }
}
/**
 * @brief 
 * 
 * @param n 
 * @param matrix_1 
 * @param matrix_2 
 */
void kijForm(
    int n,
    int p_r,
    int *m_1,
    int *m_2,
    int * r_m)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < p_r/n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                r_m[i * n + j] += m_1[i * n + k] * m_2[k * n + j];
            }
        }
    }
}

void print_result_matrix(
    int n, 
    double start_time, 
    double finish_time,
    char flag[],
    int my_rank,
    int *f_m, 
    int *rcv_buf,
    int p_r,
    int s_c[],
    int displs[]){

    MPI_Gatherv(rcv_buf, p_r, MPI_INT, f_m, s_c, 
        displs, MPI_INT, 0, MPI_COMM_WORLD);
    if(my_rank == 0){
        finish_time = MPI_Wtime();
        printf("elapsed time = %.6e seconds\n", finish_time - start_time);
       if(!strcmp(flag, "I")){
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    printf("%d ", f_m[i * n + j]);
                }
                printf("\n");
            }
      }
    }
}


void init_matrix(int n, int **t_m){
  for (int i = 0; i < n; ++i)
  {
      t_m[i] = (int *)malloc(sizeof(int *) * n);
  }
}

int main(void){

    char form[50];
    char flag[50];
    int my_rank, comm_sz, n;
    int r_m, p_r;
   // int total;
    int total_sum = 0;
    double start_time;
    double finish_time = 0;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    getUserInput(&n, form, flag, my_rank);

    // total = n * n;
    int *matrix_1 = (int *)malloc(sizeof(int) * n * n);
    int *matrix_2 = (int *)malloc(sizeof(int) * n * n);

    // int * t_m_1 = (int *)malloc(sizeof(int*)* n * n);
    // int * t_m_2 = (int *)malloc(sizeof(int*)* n * n);

    int * final_matrix = (int *)malloc(sizeof(int *) * n * n);
    int * send_counts = (int *)malloc(sizeof(int *) * comm_sz);
    int * displs = (int *)malloc(sizeof(int *) * comm_sz);

    for(int i = 0; i < comm_sz; i++){
        send_counts[i] = 0;
        displs[i] = 0;
    }
   // MPI_Bcast(&total, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int * local_m = (int *)malloc(sizeof(int *) *  n * n);
    int * local_m_2 = (int *)malloc(sizeof(int *) *  n * n);

    for(int i = 0; i < n * n; i++){
            local_m[i] = 0;
            local_m_2[i] = 0;
     }

    MPI_Barrier(MPI_COMM_WORLD);
    if (my_rank == 0)
    {
        // Record the Start Time
        printf("form:%s\n", form);
        printf("running on %d processors\n", comm_sz);
        start_time = MPI_Wtime();
    }

    r_m = n % comm_sz; //reminder
    p_r = n / comm_sz;

    if(my_rank == 0){
        if(r_m != 0){
           p_r = p_r + 1;
        }
       // printf("my_rank:%d, p_r:%d\n", my_rank, p_r);
        p_r *= n;
        MPI_Gather(&p_r, 1, MPI_INT, send_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }else{
        if(r_m > 0 && my_rank < r_m){
            p_r+=1;
        }
       // printf("my_rank:%d, p_r:%d\n", my_rank, p_r);
        p_r *= n;
        MPI_Gather(&p_r, 1, MPI_INT, send_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    MPI_Reduce(&p_r, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


    int * send_buf = (int *)malloc(sizeof(int *) * p_r);
    int * kij_buf = (int *)malloc(sizeof(int *) * n * n);
    for (int i = 0; i <  n * n; ++i)
    {
        kij_buf[i] = 0;
        /* code */
    }
    for (int i = 0; i < p_r; ++i)
    {
        send_buf[i] = 0;
    }

    if (!strcmp(flag, "R"))
    {
        random_matrix(n, my_rank, matrix_1, matrix_2);
    }
    else if (!strcmp(flag, "I"))
    {
        input_matrix(n, my_rank, matrix_1, matrix_2);
    }
    else
    {
        printf("error command I\n");
    }

    scatter_matrix(n, comm_sz, p_r, my_rank, local_m, 
        matrix_1, matrix_2, send_counts, displs);

    if (!strcmp(form, "ijk"))
    {
        ijkForm(n, p_r, local_m, 
             matrix_2, send_buf);
    }
    else if (!strcmp(form, "ikj"))
    {
         ikjForm(n, p_r, local_m, 
            matrix_2, send_buf);
    }
    else if (!strcmp(form, "kij"))
    {
        kijForm(n, p_r, local_m, matrix_2, send_buf);
    }
    // if(my_rank == 0){
    //   printf("total_sum:%d\n", total_sum);
    // }

    print_result_matrix(n, start_time, finish_time, flag, my_rank, 
        final_matrix, send_buf, p_r, send_counts, displs); 

    MPI_Finalize();
    return 0;
}

