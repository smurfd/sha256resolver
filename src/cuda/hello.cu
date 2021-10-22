#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Device code
__global__ void VecAdd(float* A, float* B, float* C, int N) {
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < N)
        C[i] = A[i] + B[i];
}

// Host code
int main() {
    int N = 3;
    size_t size = N * sizeof(float);
    srand((unsigned int) time(NULL));


    // Allocate input vectors h_A and h_B in host memory
    float* h_A = (float*)malloc(size);
    float* h_B = (float*)malloc(size);
    float* h_C = (float*)malloc(size);

    // Initialize input vectors
    // ...

    // Allocate vectors in device memory
    float* d_A;
    cudaMalloc(&d_A, size);
    float* d_B;
    cudaMalloc(&d_B, size);
    float* d_C;
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, (float*)((float)rand() / (float)(RAND_MAX)));
/*    d_A = (float*)((float)rand() / (float)(RAND_MAX));
    d_B = (float*)((float)rand() / (float)(RAND_MAX));
    d_C = (float*)((float)rand() / (float)(RAND_MAX));
    h_A = (float*)((float)rand() / (float)(RAND_MAX));
    h_B = (float*)((float)rand() / (float)(RAND_MAX));
    h_C = (float*)((float)rand() / (float)(RAND_MAX));

*/
    // Copy vectors from host memory to device memory
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // Invoke kernel
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
    VecAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

    // Copy result from device memory to host memory
    // h_C contains the result in host memory
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    printf("%d %d\n", blocksPerGrid);
    printf("d_A, h_A: %f %f\n", d_A, h_A);
    printf("d_B, h_B: %f %f\n", d_B, h_B);
    printf("d_C, h_C: %f %f\n", d_C, h_C);

    // Free device memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
            
    // Free host memory
    //...
}

