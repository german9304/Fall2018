#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

void ijkForm(int n, int matrix_1[][n], int matrix_2[][n]);

void ikjForm(int n, int matrix_1[][n], int matrix_2[][n]);

void kijForm(int n, int matrix_1[][n], int matrix_2[][n]);

void randomMatrix(int n, double matrix_1[][n], double matrix_2[][n]);

void readMatrix1(
    int n,
    int local_n, 
    double matrix_1[],
    double local_m_1[], 
    int rank);

void readMatrix2(
    int n, 
    int local_n,
    double matrix_2[][n],
    double local_m_2[], 
    int rank);

void print_matrix();

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
    int rank, comm_sz;
    // double matrix_1[n][n];
    // double local_m_2[2];
    // double final_matrix[n][n];

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    getUserInput(&n, form, flag, rank);


    local_n = (n*n) / comm_sz;
    double matrix_1[n];
    double matrix_2[n][n];
    // double matrix_2[n][n];
    double local_m_1[local_n];
    double local_m_2[local_n];


    if (!strcmp(flag, "R"))
    {
        printf("random\n");

       // randomMatrix(n, matrix_1, matrix_2);

    }
    else if (!strcmp(flag, "I"))
    {
       // printf("read matrix I\n");
       readMatrix1(n, local_n, matrix_1, local_m_1, rank);

       readMatrix2(n, local_n, matrix_2, local_m_2, rank);
    }
    else
    {
    }

   

    if(rank == 0){
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
    }else{
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
        
  


    if (!strcmp(form, "ijk"))
    {
            printf("rank:%d, ijk FORM\n", rank);
    }
    // else if (!strcmp(form, "ikj"))
    // {
    //     printf("ikj FORM\n");
    // }
    // else if (!strcmp(form, "kij"))
    // {
    //     printf("kij FORM\n");
    // }
    // else
    // {
    // }
    // print_matrix();

    MPI_Finalize();
    return 0;
}


void transpose_matrix(
    int n,
    double matrix_2[][n], 
    double transpose_matrix[][n]){

   for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
           transpose_matrix[i][j] = matrix_2[j][i];
      }//for
    }//for
}//transpose_matrix


void getUserInput(int *n, char form[], char flag[], int rank){
    if(rank == 0){
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
    }//for

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix_2[i][j] = (rand() % (100 - 0 + 1)) + 0;
        } //for
    }//for
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
 int local_n, 
 double matrix_1[], 
 double local_m_1[],
 int rank)
{
    
    if(rank == 0){
        printf("enter matrix1 values:\n");
        for (int j = 0; j < n * n; j++)
        {
            //printf("j: %d\n", j);
           scanf("%lf", &matrix_1[j]);

        } //for
        MPI_Scatter(matrix_1, local_n, MPI_DOUBLE, 
            local_m_1, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    }else{
        MPI_Scatter(matrix_1, local_n, MPI_DOUBLE, 
            local_m_1, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

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

void readMatrix2(
 int n,
 int local_n, 
 double matrix_2[][n],
 double local_m_2[],
 int rank)
{

    double transp_matr[n][n];
    double temp_matr[n * n];
    int iter = 0;
    if(rank == 0){
        printf("enter matrix2 values:\n");
        for (int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++){
                 //printf("j: %d\n", j);
             scanf("%lf", &matrix_2[i][j]);
            }
        } //for
        // MPI_Scatter(matrix_2, local_n, MPI_DOUBLE, 
        //     local_m_2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        transpose_matrix(n, matrix_2, transp_matr);
        // printf("transp_matr\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
               // printf("iter: %d, %f ", iter, transp_matr[i][j]);
                temp_matr[iter] = transp_matr[i][j];
                iter++;

            } //for
           // printf("\n");
        }//for
        // printf("final matrix\n");
        // for (int i = 0; i < n * n; i++)
        // {
        //     printf("%f \n", temp_matr[i]);

        // } //for
        MPI_Scatter(temp_matr, local_n, MPI_DOUBLE, 
            local_m_2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
     }else{
        MPI_Scatter(temp_matr, local_n, MPI_DOUBLE, 
            local_m_2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

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


/**
 * @brief 
 * 
 * @param n 
 * @param matrix_1 
 * @param matrix_2 
 */
void ijkForm(int n, int matrix_1[][n], int matrix_2[][n])
{
}
/**
 * @brief 
 * 
 * @param n 
 * @param matrix_1 
 * @param matrix_2 
 */
void ikjForm(int n, int matrix_1[][n], int matrix_2[][n])
{
}
/**
 * @brief 
 * 
 * @param n 
 * @param matrix_1 
 * @param matrix_2 
 */
void kijForm(int n, int matrix_1[][n], int matrix_2[][n])
{
}
