/*
 * scatter_gather.c
 *
 * Demonstrates MPI_Scatter and MPI_Gather:
 *
 *  - Rank 0 initialises an array of N integers.
 *  - MPI_Scatter splits the array equally among all processes.
 *  - Each process doubles its local chunk.
 *  - MPI_Gather reassembles the results on rank 0.
 *  - Rank 0 prints the final array.
 *
 * Compile:  mpicc -O2 -o scatter_gather scatter_gather.c
 * Run:      mpirun -np 4 ./scatter_gather
 *
 * Note: N must be divisible by the number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 16   /* Total array size – must be divisible by np */

int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (N % size != 0) {
        if (rank == 0)
            fprintf(stderr, "Error: N (%d) must be divisible by np (%d)\n",
                    N, size);
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    int chunkSize = N / size;

    /* --- Root process initialises the global array ------------------------- */
    int *globalArray = NULL;
    if (rank == 0) {
        globalArray = (int *)malloc(N * sizeof(int));
        printf("Initial array (rank 0):\n  ");
        for (int i = 0; i < N; i++) {
            globalArray[i] = i + 1;   /* 1, 2, 3, ..., N */
            printf("%d ", globalArray[i]);
        }
        printf("\n");
    }

    /* --- Each process allocates its local chunk ----------------------------- */
    int *localChunk = (int *)malloc(chunkSize * sizeof(int));

    /*
     * MPI_Scatter: root sends a contiguous chunk of globalArray to each rank.
     * Every process (including root) receives chunkSize integers into localChunk.
     */
    MPI_Scatter(globalArray, chunkSize, MPI_INT,
                localChunk,  chunkSize, MPI_INT,
                0, MPI_COMM_WORLD);

    /* --- Each process works on its chunk ------------------------------------ */
    for (int i = 0; i < chunkSize; i++) {
        localChunk[i] *= 2;
    }

    printf("Rank %d doubled its chunk:", rank);
    for (int i = 0; i < chunkSize; i++) {
        printf(" %d", localChunk[i]);
    }
    printf("\n");

    /*
     * MPI_Gather: collect local chunks back to root.
     */
    MPI_Gather(localChunk,  chunkSize, MPI_INT,
               globalArray, chunkSize, MPI_INT,
               0, MPI_COMM_WORLD);

    /* --- Root prints the result --------------------------------------------- */
    if (rank == 0) {
        printf("Result array after doubling (rank 0):\n  ");
        for (int i = 0; i < N; i++) {
            printf("%d ", globalArray[i]);
        }
        printf("\n");
        free(globalArray);
    }

    free(localChunk);
    MPI_Finalize();
    return 0;
}
