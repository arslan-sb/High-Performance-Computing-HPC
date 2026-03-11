/*
 * vector_addition.cu
 *
 * Classic first CUDA program: element-wise addition of two vectors.
 *
 *   C[i] = A[i] + B[i]   for i in [0, N)
 *
 * Each GPU thread handles exactly one element, making this embarrassingly
 * parallel – a perfect fit for the GPU.
 *
 * Compile:  nvcc -o vector_addition vector_addition.cu
 * Run:      ./vector_addition
 */

#include <stdio.h>
#include <stdlib.h>

#define N 1024           /* Number of elements in each vector   */
#define BLOCK_SIZE 256   /* Threads per block (must be ≤ 1024)  */

/* --------------------------------------------------------------------------
 * Error-checking macro for CUDA API calls.
 * On failure it prints the error description and aborts the program.
 * -------------------------------------------------------------------------- */
#define CUDA_CHECK(call)                                                        \
    do {                                                                        \
        cudaError_t err = (call);                                               \
        if (err != cudaSuccess) {                                               \
            fprintf(stderr, "CUDA error at %s:%d – %s\n",                      \
                    __FILE__, __LINE__, cudaGetErrorString(err));               \
            exit(EXIT_FAILURE);                                                 \
        }                                                                       \
    } while (0)

/* --------------------------------------------------------------------------
 * Kernel: each thread computes one element of C = A + B.
 * -------------------------------------------------------------------------- */
__global__ void vectorAdd(const float *A, const float *B, float *C, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {          /* Guard against out-of-bounds access  */
        C[i] = A[i] + B[i];
    }
}

/* --------------------------------------------------------------------------
 * Helper: verify the result on the host.
 * -------------------------------------------------------------------------- */
static int verify(const float *C, int n)
{
    for (int i = 0; i < n; i++) {
        float expected = (float)i + (float)(i * 2);  /* A[i]=i, B[i]=2*i */
        if (C[i] != expected) {
            fprintf(stderr, "Mismatch at index %d: got %f, expected %f\n",
                    i, C[i], expected);
            return 0;
        }
    }
    return 1;
}

/* --------------------------------------------------------------------------
 * Host (CPU) entry point
 * -------------------------------------------------------------------------- */
int main(void)
{
    size_t bytes = N * sizeof(float);

    /* --- Allocate host memory -------------------------------------------- */
    float *h_A = (float *)malloc(bytes);
    float *h_B = (float *)malloc(bytes);
    float *h_C = (float *)malloc(bytes);

    /* Initialise input vectors */
    for (int i = 0; i < N; i++) {
        h_A[i] = (float)i;
        h_B[i] = (float)(i * 2);
    }

    /* --- Allocate device (GPU) memory --------------------------------------- */
    float *d_A, *d_B, *d_C;
    CUDA_CHECK(cudaMalloc((void **)&d_A, bytes));
    CUDA_CHECK(cudaMalloc((void **)&d_B, bytes));
    CUDA_CHECK(cudaMalloc((void **)&d_C, bytes));

    /* --- Copy host → device ------------------------------------------------ */
    CUDA_CHECK(cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice));

    /* --- Launch kernel ------------------------------------------------------ */
    int blocksPerGrid = (N + BLOCK_SIZE - 1) / BLOCK_SIZE;
    printf("Vector size: %d\n", N);
    printf("Threads per block: %d, Blocks per grid: %d\n",
           BLOCK_SIZE, blocksPerGrid);

    vectorAdd<<<blocksPerGrid, BLOCK_SIZE>>>(d_A, d_B, d_C, N);

    /* --- Copy device → host ------------------------------------------------- */
    CUDA_CHECK(cudaMemcpy(h_C, d_C, bytes, cudaMemcpyDeviceToHost));

    /* --- Verify result ------------------------------------------------------- */
    if (verify(h_C, N)) {
        printf("PASSED: C = A + B computed correctly for all %d elements.\n", N);
    } else {
        printf("FAILED: result mismatch detected.\n");
    }

    /* --- Free memory --------------------------------------------------------- */
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}
