# 02 – OpenMP

An introduction to shared-memory parallelism on multi-core CPUs using OpenMP.

## Concepts Covered

| Program | Concept |
|---------|---------|
| `hello_openmp.c` | Creating threads, `omp_get_thread_num`, `omp_get_num_threads` |
| `parallel_for.c` | Loop parallelisation with `#pragma omp parallel for`, race conditions and reductions |

## Key OpenMP Directives

| Directive / Clause | Meaning |
|--------------------|---------|
| `#pragma omp parallel` | Fork a team of threads |
| `#pragma omp parallel for` | Distribute loop iterations across threads |
| `reduction(op:var)` | Each thread keeps a private copy; combined with `op` at the end |
| `private(var)` | Each thread gets its own copy of `var` |
| `shared(var)` | All threads share the same `var` (default) |
| `omp_get_num_threads()` | Returns the number of threads in the current team |
| `omp_get_thread_num()` | Returns the calling thread's ID (0-based) |

## Build & Run

```bash
make                            # compile with -fopenmp
./hello_openmp
./parallel_for

# Control thread count at runtime
OMP_NUM_THREADS=8 ./parallel_for

make clean
```

## References

- [OpenMP Specification 5.2](https://www.openmp.org/specifications/)
- [OpenMP Tutorial – LLNL](https://hpc-tutorials.llnl.gov/openmp/)
