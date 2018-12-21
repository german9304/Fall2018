/**
* @author German Razo
* file: matrixmult.c
* @brief: this programs implements the parallel version
*        of matrix multiplication in the forms ijk, ikj and kij.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>


/**
 * @brief Gets the User Input,
 *        and then core 0 sends data to all cores.
 * 
 * @param n size of matrix
 * @param form form of matrix that will be multiplied,
 *         either ijk, ikj, or kij
 * @param flag determines if matrix is generated by user
 *      or random generated. Values are I and R
 * @param rank rank of each core
 */
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
 * @brief generates the matrix entered by user
 * 
 * @param n size of matrix 
 * @param my_rank number of each core.
 * @param matrix_1 matrix a 
 * @param matrix_2 matrix b 
 */
void input_matrix(
    int n,
    int my_rank,
    int *matrix_1,
    int *matrix_2)
{

    if (my_rank == 0)
    {
        for (int i = 0; i < n * n; i++)
        {
            scanf("%d", &matrix_1[i]);
        }//for

        for (int i = 0; i < n * n; i++)
        {

            scanf("%d", &matrix_2[i]);
        }//for
    }//if
}/* input_matrix */

/**
 * @brief generates a random matrix 
 *         with numbers in the range [0 , 100] 
 *         of type int
 * 
 * @param n size of matrix
 * @param my_rank number of core
 * @param matrix_1 matrix a 
 * @param matrix_2 matrix b
 */
void random_matrix(
    int n,
    int my_rank,
    int *matrix_1,
    int *matrix_2)
{
    srand(time(0));

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
/**
 * @brief implements the distribution of rows
 *        to each core with scatterv function.
 * 
 * @param n size of matrix
 * @param comm_sz total number of cores
 * @param p_r number of elements each core will have
 * @param my_rank number of each core
 * @param local_m matrix where each core will have
 * @param matrix_1 matrix a 
 * @param matrix_2 matrix b
 * @param send_counts array that contains how many elementes
 *         each core will have from the matrix
 * @param displs array of ranges that each core will have
 */
void scatter_matrix(
    int n,
    int comm_sz,
    int p_r,
    int my_rank,
    int *local_m,
    int *matrix_1,
    int *matrix_2,
    int *send_counts,
    int *displs)
{

    if (my_rank == 0)
    {
        int sum = 0;
        for (int i = 0; i < comm_sz; i++)
        {
            displs[i] = sum;
            sum += send_counts[i];
        }
    }
    MPI_Scatterv(matrix_1, send_counts, displs, MPI_INT,
                 local_m, p_r, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(matrix_2, n * n, MPI_INT, 0, MPI_COMM_WORLD);
} /* scatter_matrix */

/**
 * @brief implements the ijk form multiplication
 * 
 * @param n size of matrix
 * @param p_r number of values each core will have
 * @param m_1 matrix a that will be multiplied 
 * @param m_2 matrix b that will be multiplied 
 * @param r_m result matrix that will store the result
 *            from the dot product of rows.
 */
void ijkForm(
    int n,
    int p_r,
    int *m_1,
    int *m_2,
    int *r_m)
{

    for (int i = 0; i < p_r / n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int sum = 0;
            for (int k = 0; k < n; k++)
            {
                sum += m_1[i * n + k] * m_2[k * n + j];
            }
            r_m[i * n + j] = sum;
        }
    }
} /* ijkForm */
/**
 * @brief implements the ijk form multiplication
 * 
 * @param n size of matrix
 * @param p_r number of values each core will have
 * @param m_1 matrix a that will be multiplied 
 * @param m_2 matrix b that will be multiplied 
 * @param r_m result matrix that will store the result
 *            from the dot product of rows.
 */
void ikjForm(
    int n,
    int p_r,
    int *m_1,
    int *m_2,
    int *r_m)
{
    for (int i = 0; i < p_r / n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            int mid = m_1[(i * n) + k];
            for (int j = 0; j < n; j++)
            {
                r_m[i * n + j] += mid * m_2[k * n + j];
            }
        }
    }
} /* ikjForm */
/**
 * @brief implements the ijk form multiplication
 * 
 * @param n size of matrix
 * @param p_r number of values each core will have
 * @param m_1 matrix a that will be multiplied 
 * @param m_2 matrix b that will be multiplied 
 * @param r_m result matrix that will store the result
 *            from the dot product of rows.
 */
void kijForm(
    int n,
    int p_r,
    int *m_1,
    int *m_2,
    int *r_m)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < p_r / n; i++)
        {
            int mid = m_1[i * n + k];
            for (int j = 0; j < n; j++)
            {
                r_m[i * n + j] += mid * m_2[k * n + j];
            }
        }
    }
} /* kijForm */
/**
 * @brief prints the resultant matrix, 
 *    from the multiplication of matrix_1 and matrix_2
 * 
 * @param n size of matrix
 * @param start_time contains the time, 
 *                when the parallel work started
 * @param finish_time contains the time, 
 *                when the parallel work finished
 * @param flag the type of flag entered by user, 
 *             either I or R
 * @param my_rank number of each core
 * @param f_m vector of type pointer int that contains 
 *             the resultant dot product from each core.
 * @param rcv_buf matrix of type pointer int that core 0
 *        will gather from every core.
 * @param p_r number of elements each core will have from 
 *            the matrix and that will send to core 0.
 * @param s_c number of elements each core will have from the 
 *            matrix and that core 0 will receive from every core.
 * @param displs range every core willl have from the resultant matrix.
 */
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
    int displs[])
{

    MPI_Gatherv(rcv_buf, p_r, MPI_INT, f_m, s_c,
                displs, MPI_INT, 0, MPI_COMM_WORLD);
    if (my_rank == 0)
    {
        finish_time = MPI_Wtime();
        printf("elapsed time = %f seconds\n", finish_time - start_time);
        if (!strcmp(flag, "I"))
        {
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
} /* print_result_matrix */
/**
 * @brief allocates memory for array inside the 2d array.
 * 
 * @param n size of matrix
 * @param t_m matrix generated by uer or random matrix
 */
void init_matrix(int n, int **t_m)
{
    for (int i = 0; i < n; ++i)
    {
        t_m[i] = (int *)malloc(sizeof(int *) * n);
    }
} /* init_matrix */

int main(void)
{

    char form[50];
    char flag[50];
    int my_rank, comm_sz, n;
    int r_m, p_r;
    double start_time;
    double finish_time = 0;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    getUserInput(&n, form, flag, my_rank);

    int *matrix_1 = (int *)malloc(sizeof(int) * n * n);
    int *matrix_2 = (int *)malloc(sizeof(int) * n * n);
    int *final_matrix = (int *)malloc(sizeof(int *) * n * n);
    int *send_counts = (int *)malloc(sizeof(int *) * comm_sz);
    int *displs = (int *)malloc(sizeof(int *) * comm_sz);

    for (int i = 0; i < comm_sz; i++)
    {
        send_counts[i] = 0;
        displs[i] = 0;
    }

    int *local_m = (int *)malloc(sizeof(int *) * n * n);
    int *local_m_2 = (int *)malloc(sizeof(int *) * n * n);

    for (int i = 0; i < n * n; i++)
    {
        local_m[i] = 0;
        local_m_2[i] = 0;
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

    MPI_Barrier(MPI_COMM_WORLD);
    if (my_rank == 0)
    {
        // Record the Start Time
        printf("running on %d processors\n", comm_sz);
        start_time = MPI_Wtime();
    }

    r_m = n % comm_sz; //reminder
    p_r = n / comm_sz;

    if (my_rank == 0)
    {
        int sum = 0;
        int c_p = p_r;
        for (int i = 0; i < comm_sz; ++i)
        {
            if (i == 0)
            {
                if (r_m != 0)
                {
                    c_p = c_p + 1;
                }
            }
            else
            {
                if (r_m > 0 && i < r_m)
                {
                    c_p += 1;
                }
            }
            c_p *= n;
            send_counts[i] = c_p;
            sum += c_p;
            c_p = p_r;
        }
    }

    if (my_rank == 0)
    {
        if (r_m != 0)
        {
            p_r = p_r + 1;
        }
        p_r *= n;
        // printf("my_rank:%d, p_r:%d\n", my_rank, p_r);
        // MPI_Gather(&p_r, 1, MPI_INT, send_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else
    {
        if (r_m > 0 && my_rank < r_m)
        {
            p_r += 1;
        }
        p_r *= n;
        //  printf("my_rank:%d, p_r:%d\n", my_rank, p_r);
        // MPI_Gather(&p_r, 1, MPI_INT, send_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    int *send_buf = (int *)malloc(sizeof(int *) * p_r);
    int *kij_buf = (int *)malloc(sizeof(int *) * n * n);
    for (int i = 0; i < n * n; ++i)
    {
        kij_buf[i] = 0;
        /* code */
    }
    for (int i = 0; i < p_r; ++i)
    {
        send_buf[i] = 0;
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

    print_result_matrix(n, start_time, finish_time, flag, my_rank,
                        final_matrix, send_buf, p_r, send_counts, displs);

    MPI_Finalize();
    return 0;
}
