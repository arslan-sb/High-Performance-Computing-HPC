# High Performance Computing (HPC) & GPU Programming

A personal learning repository for High Performance Computing and GPU programming. Each topic is organized in its own numbered folder with code examples, notes, and build instructions.

## Repository Structure

| Folder | Topic | Technologies |
|--------|-------|-------------|
| [01_CUDA_Basics](./01_CUDA_Basics/) | GPU programming fundamentals | CUDA C/C++ |
| [02_OpenMP](./02_OpenMP/) | Shared-memory CPU parallelism | OpenMP, C |
| [03_MPI](./03_MPI/) | Distributed-memory parallelism | MPI, C |

## Prerequisites

| Tool | Purpose | Install |
|------|---------|---------|
| NVIDIA CUDA Toolkit ≥ 11.0 | CUDA compilation (`nvcc`) | https://developer.nvidia.com/cuda-downloads |
| GCC ≥ 9 | C/C++ host compiler | `sudo apt install build-essential` |
| OpenMPI or MPICH | MPI runtime & compiler | `sudo apt install libopenmpi-dev openmpi-bin` |

## Quick Start

```bash
# Clone the repo
git clone https://github.com/arslan-sb/High-Performance-Computing-HPC.git
cd High-Performance-Computing-HPC

# Build & run a CUDA example
cd 01_CUDA_Basics
make
./hello_gpu

# Build & run an OpenMP example
cd ../02_OpenMP
make
./hello_openmp

# Build & run an MPI example
cd ../03_MPI
make
mpirun -np 4 ./hello_mpi
```

## Learning Path

1. **CUDA Basics** – understand the GPU execution model (threads, blocks, grids), memory hierarchy, and write your first kernels.
2. **OpenMP** – parallelize loops and tasks on multi-core CPUs with minimal code changes.
3. **MPI** – scale across multiple nodes using message passing.

## Resources

- [CUDA Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)
- [OpenMP Specification](https://www.openmp.org/specifications/)
- [MPI Tutorial](https://mpitutorial.com/)
- [NVIDIA Deep Learning Institute](https://www.nvidia.com/en-us/training/)
