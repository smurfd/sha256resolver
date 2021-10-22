import os
import pycuda.autoinit
import pycuda.driver as drv
import numpy
from pycuda.compiler import SourceModule

os.environ['PATH'] = os.environ['PATH']+":/usr/local/cuda-11.4/bin"
print(os.environ['PATH'])

mod = SourceModule("""
__global__ void multiply_them(float *dest, float *a, float *b)
{
  const int i = threadIdx.x;
  dest[i] = a[i] * b[i];
}
""")

multiply_them = mod.get_function("multiply_them")

a = numpy.random.randn(800).astype(numpy.float32)
b = numpy.random.randn(800).astype(numpy.float32)

dest = numpy.zeros_like(a)
multiply_them(drv.Out(dest), drv.In(a), drv.In(b),block=(800,1,1), grid=(1,1))

print(a)
print(b)
print(dest)
print(dest-a*b)
