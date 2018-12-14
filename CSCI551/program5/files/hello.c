
/* File:     hello.c
 *
 * Purpose:  A parallel hello, world program that uses OpenMP
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

/*-------------------------------------------------------------------
 * Function:    Hello
 * Purpose:     Thread function that prints message
 */
void Hello(char* name) {
   int my_rank = omp_get_thread_num();
   int thread_count = omp_get_num_threads();

   sleep(rand()%60+30);
   printf("Hello %s from thread %d of %d\n", name, my_rank, thread_count);

}  /* Hello */

/*--------------------------------------------------------------------*/

int main(int argc, char* argv[]) {

   if (argc != 2)
      printf("Usage: ./hello <name>\n");
   else {
      printf("There are %d processors available\n", omp_get_num_procs());
      srand (time(NULL));
   #  pragma omp parallel
      Hello(argv[1]);
   }
   return 0;

}  /* main */