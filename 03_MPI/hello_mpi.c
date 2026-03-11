/*
 * hello_mpi.c
 *
 * "Hello, World!" with MPI.
 *
 * Every MPI process prints its rank and the total number of processes.
 * This is typically the first MPI program you write.
 *
 * Compile:  mpicc -O2 -o hello_mpi hello_mpi.c
 * Run:      mpirun -np 4 ./hello_mpi
 */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char processorName[MPI_MAX_PROCESSOR_NAME];
    int nameLen;

    /* MPI_Init must be called before any other MPI function. */
    MPI_Init(&argc, &argv);

    /* MPI_COMM_WORLD is the default communicator containing all processes. */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    /* This process's ID       */
    MPI_Comm_size(MPI_COMM_WORLD, &size);    /* Total number of processes */
    MPI_Get_processor_name(processorName, &nameLen);

    printf("Hello from rank %d of %d on host \"%s\"\n",
           rank, size, processorName);

    /* MPI_Finalize must be called at the end. */
    MPI_Finalize();
    return 0;
}
