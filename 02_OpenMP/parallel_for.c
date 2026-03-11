/*
 * parallel_for.c
 *
 * Demonstrates two common OpenMP patterns:
 *
 *  1. Parallel loop  – filling an array with thread IDs.
 *  2. Reduction      – summing N integers in parallel, avoiding race conditions.
 *
 * Compile:  gcc -fopenmp -O2 -o parallel_for parallel_for.c
 * Run:      ./parallel_for
 *           OMP_NUM_THREADS=4 ./parallel_for
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 16   /* Small enough to print every element */

int main(void)
{
    /* -----------------------------------------------------------------------
     * Pattern 1: Parallel loop
     *
     * #pragma omp parallel for distributes loop iterations across threads.
     * Each thread fills its share of the array independently.
     * ----------------------------------------------------------------------- */
    int assignedThread[N];

#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        assignedThread[i] = omp_get_thread_num();
    }

    printf("Parallel loop – element to thread assignment:\n");
    for (int i = 0; i < N; i++) {
        printf("  assignedThread[%2d] = %d\n", i, assignedThread[i]);
    }

    /* -----------------------------------------------------------------------
     * Pattern 2: Reduction
     *
     * Without the reduction clause, multiple threads writing to `sum`
     * simultaneously would be a *race condition*, producing wrong results.
     *
     * reduction(+:sum) tells OpenMP to:
     *   - Give each thread a private copy of `sum` initialised to 0.
     *   - Add all private copies together at the end.
     * ----------------------------------------------------------------------- */
    long sum = 0;

#pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        sum += i;
    }

    long expected = (long)N * (N + 1) / 2;  /* Gauss formula */
    printf("\nReduction – sum of 1..%d = %ld (expected %ld) → %s\n",
           N, sum, expected, (sum == expected) ? "CORRECT" : "WRONG");

    return 0;
}
