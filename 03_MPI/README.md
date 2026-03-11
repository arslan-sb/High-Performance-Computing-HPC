# 03 – MPI (Message Passing Interface)

An introduction to distributed-memory parallelism using MPI.

## Concepts Covered

| Program | Concept |
|---------|---------|
| `hello_mpi.c` | Process rank, communicator size, `MPI_Init` / `MPI_Finalize` |
| `scatter_gather.c` | `MPI_Scatter`, `MPI_Gather`, distributed array processing |

## Key MPI Concepts

| Concept | Meaning |
|---------|---------|
| **Rank** | Unique integer ID of a process within a communicator (0-based) |
| **Communicator** | Group of processes that can exchange messages (`MPI_COMM_WORLD` = all) |
| **Point-to-point** | Communication between two specific processes (`MPI_Send` / `MPI_Recv`) |
| **Collective** | Communication involving all processes in a communicator (`MPI_Bcast`, `MPI_Reduce`, …) |
| `MPI_Init` | Must be called before any other MPI function |
| `MPI_Finalize` | Must be called at the end; no MPI calls are valid after this |

## Build & Run

```bash
make                          # compile with mpicc
mpirun -np 4 ./hello_mpi      # launch 4 MPI processes
mpirun -np 4 ./scatter_gather

make clean
```

## References

- [MPI Standard 4.0](https://www.mpi-forum.org/docs/)
- [MPI Tutorial (mpitutorial.com)](https://mpitutorial.com/)
- [LLNL MPI Tutorial](https://hpc-tutorials.llnl.gov/mpi/)
