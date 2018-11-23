#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

void ijkForm(int n, int matrix_1[][n], int matrix_2[][n]);

void ikjForm(int n, int matrix_1[][n], int matrix_2[][n]);

void kijForm(int n, int matrix_1[][n], int matrix_2[][n]);

void randomMatrix(int n, double matrix_1[][n], double matrix_2[][n]);

void inputMatrix(int n, double matrix_1[][n], double matrix_2[][n]);

void print_matrix();

void getUserInput();

int main(void)
{
    char form[50];
    char flag[50];
    int n;
    int my_rank, comm_sz;
    scanf("%s", form);
    scanf("%s", flag);
    scanf("%d", &n);

    double matrix_1[n][n];
    double matrix_2[n][n];
    // double final_matrix[n][n];

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (!strcmp(flag, "R"))
    {
        randomMatrix(n, matrix_1, matrix_2);
    }
    else if (!strcmp(flag, "I"))
    {
        inputMatrix(n, matrix_1, matrix_2);
    }
    else
    {
    }

    if (!strcmp(form, "ijk"))
    {
        printf("ijk FORM\n");
    }
    else if (!strcmp(form, "ikj"))
    {
        printf("ikj FORM\n");
    }
    else if (!strcmp(form, "kij"))
    {
        printf("kij FORM\n");
    }
    else
    {
    }
    // print_matrix();

    MPI_Finalize();
    return 0;
}

void getUserInput()
{
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
void inputMatrix(int n, double matrix_1[][n], double matrix_2[][n])
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &matrix_1[i][j]);
        } //for
    }     //for
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &matrix_2[i][j]);
        } //for
    }     //for

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
