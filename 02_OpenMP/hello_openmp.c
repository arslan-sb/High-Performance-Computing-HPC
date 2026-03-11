/*
 * hello_openmp.c
 *
 * "Hello, World!" with OpenMP.
 *
 * Each thread prints its ID and the total number of threads in the team.
 *
 * Compile:  gcc -fopenmp -O2 -o hello_openmp hello_openmp.c
 * Run:      ./hello_openmp
 *           OMP_NUM_THREADS=8 ./hello_openmp
 */

#include <stdio.h>
#include <omp.h>

int main(void)
{
    /*
     * #pragma omp parallel
     *   Forks a team of threads.  Every statement inside the structured
     *   block is executed by all threads simultaneously.
     */
#pragma omp parallel
    {
        int threadId   = omp_get_thread_num();
        int numThreads = omp_get_num_threads();

        /* printf is thread-safe; output lines may interleave between threads. */
        printf("Hello from thread %d of %d\n", threadId, numThreads);
    }
    /* Implicit barrier: all threads join here before main continues. */

    return 0;
}
