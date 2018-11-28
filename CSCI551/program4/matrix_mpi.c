#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>



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

/**
 * @brief 
 * 
 * @param n 
 * @param matrix_1 
 * @param matrix_2 
 */
void input_matrix(
    char form[],
    int n,
    int comm_sz,
    int p_r,
    int my_rank, 
    double local_m[],
    double matrix_1[][n],
    double matrix_2[][n],
    double t_m[][n],
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

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%lf", &matrix_2[i][j]);
            }
        } //for
    }

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
        MPI_Scatterv(t_m, send_counts, displs, MPI_DOUBLE, 
        local_m, p_r, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }else{
        MPI_Scatterv(matrix_1, send_counts, displs, MPI_DOUBLE, 
        local_m, p_r, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    MPI_Bcast(matrix_2, n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);



}

void readMatrix2(
    char form[],
    int n,
    int comm_sz,
    double matrix_2[][n],
    double t_m[n][n],
    int rank)
{
    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%lf", &matrix_2[i][j]);
            }
        } //for
    }

    // transpose_matrix(n, matrix_2, t_m);
    MPI_Bcast(matrix_2, n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
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
    double m_1[],
    double m_2[][n],
    double t_m[][n],
    double r_m[])
{
    // /*
    //  serial program one processor 
    // */
    // printf("my_rank:%d, p_r:%d", my_rank, p_r);
    transpose_matrix(n, m_2, t_m);
    double res = 0.0;
    for (int i = 0; i < p_r/n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                // int ind = (i * n + k);
                // printf("%f * %f ", m_1[ind] , m_2[j][k]);
                // res += m_1[i * n + k] * t_m[j][k];
               //  printf("%d ", i * n + j);
                r_m[i * n + j] += m_1[i * n + k] * t_m[j][k];
                // printf("[%d][%d] ", i, j);
                // printf("\n");
                /* code */
            }
        }
         // printf("\n");
    }
   //  printf("rank:%d \n", my_rank);
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
    double m_1[],
    double m_2[][n],
    double r_m[])
{
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         printf("%f ", m_2[i][j]);
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < p_r/n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            // int ind_res = (i * n) + k;
            // double res = 0.0;
            for (int j = 0; j < n; j++)
            {
                // int ind = (i * n + j);
                // int mult = (n * j + k);
                // local_result[ind] += (local_m_1[ind_res] * recvData[ind]);
                // printf("rank:%d, %d , %d, %d \n", my_rank, ind, ind_res, mult);
                // local_result[ind] += (local_m_1[ind_res] * m_2[k][j]);
                printf("rank:%d, %f * %f \n",
                my_rank,  m_1[(i * n) + k], m_2[k][j]);
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
    int my_rank,
    int p_r,
    double m_1[],
    double m_2[][n],
    double r_m[])
{
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         printf("%f ", m_1[i * n + j]);
    //     }
    //     printf("\n");
    // }
    // }
 
    for (int k = 0; k < p_r/n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            int ind_res = (k * n) + i;
            // double res = 0.0;
            for (int j = 0; j < n; j++)
            {
                int ind = (k * n + j);
                int mult = (n * j + j);
                // local_result[mult] += (local_m_1[ind_res] * recvData[ind]);
                // printf("rank:%d, %d , %d, %d \n", my_rank, ind, ind_res, mult);
                // local_result[ind] += (local_m_1[ind_res] * recvData[mult]);
              printf("%f * %f \n", m_1[(k * n) + i],
                m_2[k][j]/*, local_result[ind]*/);
                // res+= (local_m_1[ind_res] * recvData[ind]);
                // local_result[ind_res]
            }
            // printf("res: %f\n", res);
            //printf("\n");
        }
    }
}

void print_result_matrix(
    int n, 
    int my_rank,
    double f_m[], 
    double rcv_buf[],
    int p_r,
    int s_c[],
    int displs[]){
    if(my_rank == 0){
        MPI_Gatherv(rcv_buf, p_r, MPI_DOUBLE, f_m, s_c, 
            displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        printf("my_rank:%d \n", my_rank);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                printf("%d ", (int) f_m[i * n + j]);
            }
            printf("\n");
        }
    }else{
        printf("my_rank:%d \n", my_rank);
        MPI_Gatherv(rcv_buf, p_r, MPI_DOUBLE, f_m, s_c, 
            displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
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
    double matrix_2[n][n];
    double final_matrix[n * n];

    double t_m[n][n];
    int send_counts[comm_sz];
    int displs[comm_sz];

    for(int i = 0; i < comm_sz; i++){
        send_counts[i] = 0;
        displs[i] = 0;
    }
    // MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&total, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double local_m[n * n];
    // for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            local_m[j] = 0;
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

    double send_buf[p_r];
    for (int i = 0; i < p_r; ++i)
    {
        send_buf[i] = 0.0;
    }
    if (!strcmp(flag, "R"))
    {
        printf("random\n");

        // randomMatrix(n, matrix_1, matrix_2);
    }
    else if (!strcmp(flag, "I"))
    {
        // printf("read matrix I\n");
        input_matrix(form, n, comm_sz, p_r, my_rank, local_m, 
            matrix_1, matrix_2, t_m, send_counts, displs);
        // readMatrix2(form, n, comm_sz, matrix_2, t_m, my_rank);
        // readMatrix2();
    }
    else
    {
        printf("error command I\n");
    }

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
        kijForm(n, my_rank, p_r, local_m, 
            matrix_2, send_buf);
    }
    else
    {
        printf("rank:%d error command ijk\n", my_rank);
    }



    if(my_rank == 0){
      printf("total_sum:%d\n", total_sum);
    }

    print_result_matrix(n, my_rank, final_matrix, 
        send_buf, p_r, send_counts, displs); 

    MPI_Finalize();
	return 0;
}

