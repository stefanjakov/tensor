#include "../include/tensor.hpp"
#include <cuda_runtime.h>
#include <iostream>

__global__ void addKernel(int *c, int a, int b)
{
    *c = a + b;
}