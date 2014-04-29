#include "stdio.h"

#include "cuda.h"
#include "cuda_runtime_api.h"

//#include "utils.h"

#include <iostream>
using namespace std;


#ifndef CHECKCUDAERRORS_H
#define CHECKCUDAERRORS_H

#include <cuda_runtime_api.h>
#include <stdio.h>

#include "Point3D.h"

int CudaCheckLastError()
{
    cudaError_t error = cudaGetLastError();
    if(error != cudaSuccess)
    {
        // print the CUDA error message and exit
        printf("CUDA error: %s\n", cudaGetErrorString(error));
        fflush(stdout);
        return 1;
        //exit(-1);
    }
    printf("no errors\n");
    fflush(stdout);
    return 0;
}

#endif // CHECKCUDAERRORS_H


__global__
void operationKernel(Point3D* d_points, const int count)
{
    int myId = threadIdx.x + blockDim.x * blockIdx.x;
    if (count <= myId)
    {
        return;
    }
    d_points[myId]._y = myId;
}


void CallKernel(Point3D* h_points, const int count)
{
    const int threads = 16;
    const dim3 gridSize((count + threads - 1) / threads);
    const dim3 blockSize(threads);

    const size_t memLen = sizeof(Point3D) * count;
    Point3D* d_points;
    cudaMalloc((void**)&d_points, memLen );
    cudaMemcpy(d_points, h_points, memLen, cudaMemcpyHostToDevice);
    CudaCheckLastError();

    operationKernel<<<gridSize, blockSize>>>(d_points, count);

    cudaDeviceSynchronize();

    cudaMemcpy(h_points, d_points, memLen, cudaMemcpyDeviceToHost);
    cudaFree(d_points);
}
