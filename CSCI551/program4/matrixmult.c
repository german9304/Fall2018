#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

void ijkForm(
    int n,
    int local_iter,
    int rank,
    int local_n,
    double local_m_1[],
    double local_m_2[],
    double local_result[]);

void ikjForm(
    int n,
    int rank,
    int local_n,
    double local_m_1[],
    double local_m_2[],
    double local_result[]);

void kijForm(
    int n,
    int rank,
    int local_n,
    double local_m_1[],
    double local_m_2[],
    double local_result[]);

void randomMatrix(int n, double matrix_1[][n], double matrix_2[][n]);

void readMatrix1(
    char form[],
    int n,
    int local_n,
    double matrix_1[][n],
    double local_m_1[],
    int rank);

void readMatrix2(
    char form[],
    int n,
    int local_n,
    double matrix_2[][n],
    double local_m_2[],
    int rank);

void print_matrix(
    int n,
    int rank,
    int local_n,
    double local_result[]);

void print_matrices(
    int local_n,
    int rank,
    double local_m_1[],
    double local_m_2[]);

void transpose_matrix(
    int n,
    double matrix_2[][n],
    double transpose_matrix[][n]);

void getUserInput(int *n, char form[], char flag[], int rank);

int main(void)
{
    char form[50];
    char flag[50];
    int n, local_n;
    int local_iter = 0;
    int rank, comm_sz;
    // double matrix_1[n][n];
    // double local_m_2[2];
    // double final_matrix[n][n];

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    getUserInput(&n, form, flag, rank);

    local_n = (n * n) / comm_sz;
    double matrix_1[n][n];
    double matrix_2[n][n];
    // double matrix_2[n][n];
    double local_m_1[local_n];
    double local_m_2[local_n];
    printf("local_n: %d\n", local_n);
    double local_result[local_n];

    if (!strcmp(flag, "R"))
    {
        printf("random\n");

        // randomMatrix(n, matrix_1, matrix_2);
    }
    else if (!strcmp(flag, "I"))
    {
        // printf("read matrix I\n");
        readMatrix1(form, n, local_n, matrix_1, local_m_1, rank);

        readMatrix2(form, n, local_n, matrix_2, local_m_2, rank);
    }
    else
    {
        printf("error command\n");
    }

    if (!strcmp(form, "ijk"))
    {
        ijkForm(n, local_iter, rank, local_n,
                local_m_1, local_m_2, local_result);
    }
    else if (!strcmp(form, "ikj"))
    {
        ikjForm(n, rank, local_n, local_m_1,
                local_m_2, local_result);
    }
    else if (!strcmp(form, "kij"))
    {
        kijForm(n, rank, local_n, local_m_1,
         local_m_2,local_result);
    }
    else
    {
        printf("error command\n");
    }

    print_matrix(n, rank, local_n, local_result);

    MPI_Finalize();
    return 0;
}

void print_matrix(int n, int rank, int local_n, double local_result[])
{
    double rcv_result[n * n];
    if (rank == 0)
    {
        MPI_Gather(local_result, local_n, MPI_DOUBLE,
                   rcv_result, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        int iter = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%f ", rcv_result[iter]);
                iter++;
            }
            printf("\n");
        }
    }
    else
    {
        MPI_Gather(local_result, local_n, MPI_DOUBLE,
                   rcv_result, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
}

void transpose_matrix(
    int n,
    double matrix_2[][n],
    double transpose_matrix[][n])
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
void randomMatrix(int n, double matrix_1[][n], double matrix_2[][n])
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix_1[i][j] = (rand() % (100 - 0 + 1)) + 0;
        } //for
    }     //for

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix_2[i][j] = (rand() % (100 - 0 + 1)) + 0;
        } //for
    }     //for
}

/**
 * @brief 
 * 
 * @param n 
 * @param matrix_1 
 * @param matrix_2 
 */
void readMatrix1(
    char form[],
    int n,
    int local_n,
    double matrix_1[][n],
    double local_m_1[],
    int rank)
{

    if (rank == 0)
    {
        printf("enter matrix1 values:\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //printf("j: %d\n", j);
                scanf("%lf", &matrix_1[i][j]);
            }
        } //for
    }
    if (!strcmp(form, "kij"))
    {
        double transp_matr[n][n];
        transpose_matrix(n, matrix_1, transp_matr);
        MPI_Scatter(transp_matr, local_n, MPI_DOUBLE,
                    local_m_1, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatter(matrix_1, local_n, MPI_DOUBLE,
                    local_m_1, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    //  printf("matrix1\n");
    // for (int i = 0; i < local_n; i++)
    // {
    //         printf("%lf \n", local_m_1[i]);
    // }     //for
    //printf("matrix1\n");
    // for (int i = 0; i < n; i++)
    // {
    // for (int j = 0; j < n * n; j++)
    // {
    //     printf("%lf \n", matrix_1[j]);
    // } //for
    //printf("\n");
    // }     //for
    //  printf("matrix2\n");
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%lf ", matrix_2[i][j]);
    //     } //for
    //     printf("\n");
    // }     //for
}

void readMatrix2(
    char form[],
    int n,
    int local_n,
    double matrix_2[][n],
    double local_m_2[],
    int rank)
{

    // double temp_matr[n * n];
    // int iter = 0;
    if (rank == 0)
    {
        printf("enter matrix2 values:\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //printf("j: %d\n", j);
                scanf("%lf", &matrix_2[i][j]);
            }
        } //for
          // MPI_Scatter(matrix_2, local_n, MPI_DOUBLE,
          //     local_m_2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
          // if(!strcmp(form, "ijk")){
          //     transpose_matrix(n, matrix_2, transp_matr);
          //      MPI_Scatter(transp_matr, local_n, MPI_DOUBLE,
          //     local_m_2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
          // }else{
          //      MPI_Scatter(matrix_2, local_n, MPI_DOUBLE,
          //     local_m_2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
          // }
          // printf("transp_matr\n");
          // for (int i = 0; i < n; i++)
          // {
          //     for (int j = 0; j < n; j++)
          //     {
          //        // printf("iter: %d, %f ", iter, transp_matr[i][j]);
          //         temp_matr[iter] = transp_matr[i][j];
          //         iter++;

        //     } //for
        // printf("\n");
        // }//for
        // printf("final matrix\n");
        // for (int i = 0; i < n * n; i++)
        // {
        //     printf("%f \n", temp_matr[i]);

        // } //for
    }
    if (!strcmp(form, "ijk"))
    {
        double transp_matr[n][n];
        transpose_matrix(n, matrix_2, transp_matr);
        MPI_Scatter(transp_matr, local_n, MPI_DOUBLE,
                    local_m_2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatter(matrix_2, local_n, MPI_DOUBLE,
                    local_m_2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    // printf("matrix2\n");
    // for (int i = 0; i < n * n; i++)
    // {
    //         printf("%lf \n", local_m_2[i]);
    // }     //for

    // printf("matrix1\n");
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%lf ", matrix_1[i][j]);
    //     } //for
    //     printf("\n");
    // }     //for
    //  printf("matrix2\n");
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%lf ", matrix_2[i][j]);
    //     } //for
    //     printf("\n");
    // }     //for
}

void print_matrices(
    int local_n,
    int rank,
    double local_m_1[],
    double local_m_2[])
{

    if (rank == 0)
    {
        //printf("rank inside 0\n");
        // printf("rank:%d\n", rank);
        for (int i = 0; i < local_n; ++i)
        {
            printf("rank: %d, %lf\n", rank, local_m_1[i]);
        }
        for (int i = 0; i < local_n; ++i)
        {
            printf("rank: %d, %lf\n", rank, local_m_2[i]);
        }
    }
    else
    {
        for (int i = 0; i < local_n; ++i)
        {
            printf("rank: %d, %lf\n", rank, local_m_1[i]);
        }
        // printf("local_m_2  rank:%d\n", rank);
        for (int i = 0; i < local_n; ++i)
        {
            printf("rank: %d, %lf\n", rank, local_m_2[i]);
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
void ijkForm(
    int n,
    int local_iter,
    int rank,
    int local_n,
    double local_m_1[],
    double local_m_2[],
    double local_result[])
{
    rank++;
    local_iter++;
    //print_matrices(local_n, rank, local_m_1, local_m_2);
    double recvData[n * n];
    // if(rank == 0){
    MPI_Allgather(local_m_2, local_n, MPI_DOUBLE,
                  recvData, local_n, MPI_DOUBLE, MPI_COMM_WORLD);
    // printf("all gather matrix\n");
    // for(int i = 0; i < n * n; i++){
    //     printf("%f \n", recvData[i]);
    // }
    // printf("local_m_1\n");
    // for(int i = 0; i < local_n; i++){
    //     printf("%f \n", local_m_1[i]);
    // }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int ind_res = (i * n) + j;
            // double res = 0.0;
            for (int k = 0; k < n; k++)
            {
                int ind = (i * n + k);
                int mult = (n * j + k);
                //local_result[ind] += (local_m_1[ind] * recvData[mult]);
                // printf("rank:%d, %d , %d , %d \n", rank, ind, mult, ind_res);
                local_result[ind_res] += (local_m_1[ind] * recvData[mult]);
                // printf("%f * %f \n", local_m_1[ind], recvData[mult]);
            }
            // printf("res: %f\n", res);
            //printf("\n");
        }
    }

    // }else{
    // MPI_Allgather(local_m_2, local_n, MPI_DOUBLE,
    //  recvData, local_n, MPI_DOUBLE, MPI_COMM_WORLD);
    //}

    // for(int i = 0; i < n; i++){

    // }

    // }
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
    int rank,
    int local_n,
    double local_m_1[],
    double local_m_2[],
    double local_result[])
{
    double recvData[n * n];
    // if(rank == 0){
    // local_result[0] = 23;
    MPI_Allgather(local_m_2, local_n, MPI_DOUBLE,
                  recvData, local_n, MPI_DOUBLE, MPI_COMM_WORLD);
    rank++;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int ind_res = (i * n) + j;
            // double res = 0.0;
            for (int k = 0; k < n; k++)
            {
                int ind = (i * n + k);
                int mult = (n * j + k);
                // local_result[ind] += (local_m_1[ind_res] * recvData[ind]);
                // printf("rank:%d, %d , %d, %d \n", rank, ind, ind_res, mult);
                local_result[ind] += (local_m_1[ind_res] * recvData[mult]);
                // printf("%f * %f = %f \n", local_m_1[ind_res],
                // recvData[mult], local_result[ind]);
                // res+= (local_m_1[ind_res] * recvData[ind]);
                // local_result[ind_res]
            }
            // printf("res: %f\n", res);
            //printf("\n");
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
    int rank,
    int local_n,
    double local_m_1[],
    double local_m_2[],
    double local_result[])
{
    double recvData[n * n];
    // local_result[0] = 0.0;
    MPI_Allgather(local_m_2, local_n, MPI_DOUBLE,
                  recvData, local_n, MPI_DOUBLE, MPI_COMM_WORLD);
    // printf("all gather matrix\n");
    // for (int i = 0; i < n * n; i++)
    // {
    //     printf("%f \n", recvData[i]);
    // }
    // printf("local_m_1\n");
    // for (int i = 0; i < local_n; i++)
    // {
    //     printf("%f \n", local_m_1[i]);
    // }
    rank++;
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
        {
            int ind_res = (i * n) + j;
            // double res = 0.0;
            for (int k = 0; k < n; k++)
            {
                int ind = (i * n + k);
                int mult = (n * j + k);
                local_result[mult] += (local_m_1[ind_res] * recvData[ind]);
                // printf("rank:%d, %d , %d, %d \n", rank, ind, ind_res, mult);
                // local_result[ind] += (local_m_1[ind_res] * recvData[mult]);
               // printf("%f * %f \n", local_m_1[ind_res],
                 // recvData[ind]/*, local_result[ind]*/);
                // res+= (local_m_1[ind_res] * recvData[ind]);
                // local_result[ind_res]
            }
            // printf("res: %f\n", res);
            //printf("\n");
        }
    }
}
