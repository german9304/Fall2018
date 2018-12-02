#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>      
#include <mpi.h>



void transpose_matrix(
    int n,
    int matrix_2[][n],
    int transpose_matrix[][n])
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            transpose_matrix[i][j] = matrix_2[j][i];
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
    int matrix_1[][n],
    int matrix_2[][n])
{

    if (my_rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //printf("j: %d\n", j);
                scanf("%d", &matrix_1[i][j]);
            }
        } //for

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%d", &matrix_2[i][j]);
            }
        } //for
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
    int matrix_1[][n],
    int matrix_2[][n])
{
    srand (time(0));

    if (my_rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //printf("j: %d\n", j);
               // scanf("%lf", &matrix_1[i][j]);
                matrix_1[i][j] = rand() % 100;
            }
        } //for

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
               //  scanf("%lf", &matrix_2[i][j]);
                matrix_2[i][j] = rand() % 100;
            }
        } //for
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

void scatter_matrix(
    char form[],
    int n, 
    int comm_sz,
    int p_r,
    int my_rank, 
    int local_m[],
    int local_m_2[],
    int matrix_1[][n],
    int matrix_2[][n],
    int t_m[][n],
    int send_counts[],
    int displs[n]){

    if(my_rank == 0){
        int sum = 0;
        for(int i = 0; i < comm_sz; i++){
            displs[i] = sum;
            sum += send_counts[i];
        }
    }
    
    if (!strcmp(form, "kij"))
    {
        transpose_matrix(n, matrix_1, t_m);

        MPI_Scatterv(t_m, send_counts, displs, MPI_INT, 
        local_m, p_r, MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Scatterv(matrix_2, send_counts, displs, MPI_INT, 
        local_m_2, p_r, MPI_INT, 0, MPI_COMM_WORLD);

    }else{
        MPI_Scatterv(matrix_1, send_counts, displs, MPI_INT, 
        local_m, p_r, MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Bcast(matrix_2, n * n, MPI_INT, 0, MPI_COMM_WORLD);
    }
}

void readMatrix2(
    char form[],
    int n,
    int comm_sz,
    int matrix_2[][n],
    int t_m[n][n],
    int rank)
{
    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%d", &matrix_2[i][j]);
            }
        } //for
    }

    // transpose_matrix(n, matrix_2, t_m);
    //  if (strcmp(form, "kij"))
    // {
    //     MPI_Bcast(matrix_2, n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // }
    // if (!strcmp(form, "ijk"))
    // {
    //     // double transp_matr[n][n];
    //     transpose_matrix(n, matrix_2, transp_matr);
    //     MPI_Scatter(transp_matr, local_n, MPI_DOUBLE,
    //                 local_m_2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // }
    // else
    // {
    //     MPI_Scatter(matrix_2, local_n, MPI_DOUBLE,
    //                 local_m_2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // }
    // printf("matrix2\n");
    // for (int i = 0; i < n * n; i++)
    // {
    //         printf("%lf \n", local_m_2[i]);
    // }     //for

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
    int my_rank,
    int p_r,
    int m_1[],
    int m_2[][n],
    int t_m[][n],
    int r_m[])
{
    transpose_matrix(n, m_2, t_m);
    for (int i = 0; i < p_r/n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                r_m[i * n + j] += m_1[i * n + k] * t_m[j][k];
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
    int my_rank,
    int p_r,
    int m_1[],
    int m_2[][n],
    int r_m[])
{
    for (int i = 0; i < p_r/n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            for (int j = 0; j < n; j++)
            {
                r_m[i * n + j] += m_1[(i * n) + k] * m_2[k][j];
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
    int comm_sz,
    int my_rank,
    int p_r,
    int m_1[],
    int local_m_2[],
    int m_2[][n],
    int t_m[][n],
    int r_m[], 
    int sikj_b[])
{
    transpose_matrix(n, m_2, t_m);
    for (int k = 0; k < p_r/n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            int ind_res = i * n + k;
            for (int j = 0; j < n; j++)
            {
                int ind = (k * n + i);
                int mult = (k * n + j);
                sikj_b[i * n + j] += m_1[k * n + i] * local_m_2[k * n + j];
            }
        }
    }
}

void print_result_matrix(
    int n, 
    int comm_sz,
    char form[],
    int my_rank,
    int f_m[], 
    int rcv_buf[],
    int kij_buf[],
    int p_r,
    int s_c[],
    int displs[]){
    if(!strcmp(form, "kij")){
        MPI_Reduce(kij_buf, f_m, n * n, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    }else{
        MPI_Gatherv(rcv_buf, p_r, MPI_INT, f_m, s_c, 
            displs, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if(my_rank == 0){
        // printf("my_rank:%d \n", my_rank);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                printf("%d ", f_m[i * n + j]);
            }
            printf("\n");
        }
    }// }else{
    //    // printf("my_rank:%d \n", my_rank);
    //     MPI_Gatherv(rcv_buf, p_r, MPI_DOUBLE, f_m, s_c, 
    //         displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // }
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
    int matrix_1[n][n];
    int matrix_2[n][n];
    int final_matrix[n * n];

    int t_m[n][n];
    int send_counts[comm_sz];
    int displs[comm_sz];

    for(int i = 0; i < comm_sz; i++){
        send_counts[i] = 0;
        displs[i] = 0;
    }
    // MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&total, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int local_m[n * n];
    int local_m_2[n * n];
    // for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            local_m[j] = 0.0;
            local_m_2[n * n] = 0.0;
        }
    // }

    r_m = n % comm_sz; //reminder
    p_r = n / comm_sz;

    if(my_rank == 0){
        if(r_m != 0){
           p_r = p_r + 1;
        }
        // printf("p_r:%d\n", p_r);
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

    int send_buf[p_r];
    int kij_buf[p_r/n * n * n];
    for (int i = 0; i < p_r/n * n * n; ++i)
    {
        kij_buf[i] = 0.0;
        /* code */
    }

    // printf("after p_r:%d\n", p_r/n * n * n);
    // MPI_Bcast(test_buf, p_r * p_r, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < p_r; ++i)
    {
        send_buf[i] = 0;
       //  kij_buf[p_r/n * n * n] = 0.0;
    }
    if (!strcmp(flag, "R"))
    {
        // randomMatrix(n, matrix_1, matrix_2);
        // readMatrix2(form, n, comm_sz, matrix_2, t_m, my_rank);
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

    scatter_matrix(form, n, comm_sz, p_r, my_rank, local_m, 
        local_m_2, matrix_1, matrix_2, t_m, send_counts, displs);

    if (!strcmp(form, "ijk"))
    {
        ijkForm(n, my_rank, p_r, local_m, 
            matrix_2, t_m, send_buf);
    }
    else if (!strcmp(form, "ikj"))
    {
         ikjForm(n, my_rank, p_r, local_m, 
            matrix_2, send_buf);
    }
    else if (!strcmp(form, "kij"))
    {
        // MPI_Bcast(send_buf, n , MPI_DOUBLE, 0, MPI_COMM_WORLD);
        kijForm(n, comm_sz, my_rank, p_r, local_m, 
            local_m_2, matrix_2, t_m, send_buf, kij_buf);
    }
    else
    {
        printf("rank:%d error command ijk\n", my_rank);
    }



    if(my_rank == 0){
      printf("total_sum:%d\n", total_sum);
    }

    print_result_matrix(n, comm_sz, form, my_rank, final_matrix, 
        send_buf, kij_buf, p_r, send_counts, displs); 

    MPI_Finalize();
	return 0;
}

