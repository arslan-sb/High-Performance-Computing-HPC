# 01 – CUDA Basics

An introduction to GPU programming with NVIDIA CUDA.

## Concepts Covered

| Program | Concept |
|---------|---------|
| `hello_gpu.cu` | Launching a kernel, thread/block indexing |
| `vector_addition.cu` | Device memory allocation, `cudaMalloc`/`cudaMemcpy`, parallel element-wise operations |

## Key CUDA Vocabulary

| Term | Meaning |
|------|---------|
| **Thread** | Smallest unit of execution on the GPU |
| **Block** | Group of threads that share shared memory and can synchronize |
| **Grid** | Collection of all blocks launched by a single kernel call |
| **Warp** | 32 threads that execute together in lock-step (hardware unit) |
| **Kernel** | A function that runs on the GPU, decorated with `__global__` |
| `cudaMalloc` | Allocate memory on the device (GPU) |
| `cudaMemcpy` | Copy data between host (CPU) and device (GPU) |
| `cudaFree` | Free device memory |

## GPU Execution Model

```
Grid
└── Block (0,0)  Block (0,1)  ...
    └── Thread (0,0)  Thread (0,1)  ...
```

Each thread knows its position via:
- `threadIdx.{x,y,z}` – index within its block
- `blockIdx.{x,y,z}`  – index of the block within the grid
- `blockDim.{x,y,z}`  – number of threads per block
- `gridDim.{x,y,z}`   – number of blocks in the grid

## Build & Run

```bash
make          # compile all examples with nvcc
./hello_gpu
./vector_addition
make clean    # remove compiled binaries
```

## References

- [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)
- [CUDA Runtime API](https://docs.nvidia.com/cuda/cuda-runtime-api/)
- [NVIDIA CUDA Samples](https://github.com/NVIDIA/cuda-samples)
