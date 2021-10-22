#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""A small demo showcasing pycuda's built-in reduction kernel."""
import os
import numpy as np
import pycuda.autoinit
import pycuda.compiler
import pycuda.driver as driver
import pycuda.gpuarray as gpuarray
import pycuda.reduction

os.environ['PATH'] = os.environ['PATH']+":/usr/local/cuda-11.4/bin"

print(os.environ['PATH'])

if __name__ == '__main__':
    array_size = 10000000000 

    print(array_size)
    start, end = driver.Event(), driver.Event()

    # Allocate some random numbers
    h_array = np.random.randint(0, array_size, size=array_size).astype(np.int32)
    true_max = h_array.max()  # For verification

    # Allocate device memory and transfer host array
    d_array = gpuarray.to_gpu(h_array)

    # Create a reduction kernel
    reduction_kernel =\
        pycuda.reduction.ReductionKernel(np.int32, neutral="-1",
                                         reduce_expr="max(a, b)",
                                         map_expr="in[i]",
                                         arguments="int* const in")

    start.record()

    # Launch the reduction kernel
    gpu_max = reduction_kernel(d_array).get()

    end.record()
    end.synchronize()
    print("Took {}ms".format(start.time_till(end)))

    # Sanity check
    print("True max is {}\nGPU max is {}".format(true_max, gpu_max))
    assert gpu_max == true_max
