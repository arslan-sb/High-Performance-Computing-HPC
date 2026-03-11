/*
 * hello_gpu.cu
 *
 * The "Hello, World!" of CUDA programming.
 *
 * Each thread prints its global thread ID.  The global ID is computed as:
 *
 *   global_id = blockIdx.x * blockDim.x + threadIdx.x
 *
 * Compile:  nvcc -o hello_gpu hello_gpu.cu
 * Run:      ./hello_gpu
 */

#include <stdio.h>

/* --------------------------------------------------------------------------
 * Kernel: runs on the GPU.
 * The __global__ qualifier marks a function as a CUDA kernel.
 * -------------------------------------------------------------------------- */
__global__ void helloKernel(void)
{
    int globalId = blockIdx.x * blockDim.x + threadIdx.x;
    printf("Hello from GPU! block=%d, thread=%d, globalId=%d\n",
           blockIdx.x, threadIdx.x, globalId);
}

/* --------------------------------------------------------------------------
 * Host (CPU) entry point
 * -------------------------------------------------------------------------- */
int main(void)
{
    /* Launch configuration: 2 blocks of 4 threads each = 8 threads total. */
    int blocksPerGrid  = 2;
    int threadsPerBlock = 4;

    printf("Launching kernel with %d block(s) x %d thread(s) = %d total threads\n",
           blocksPerGrid, threadsPerBlock, blocksPerGrid * threadsPerBlock);

    /* <<< blocks, threads >>> is the CUDA launch syntax. */
    helloKernel<<<blocksPerGrid, threadsPerBlock>>>();

    /* Wait for all GPU threads to finish before the host continues. */
    cudaDeviceSynchronize();

    printf("Done.\n");
    return 0;
}
