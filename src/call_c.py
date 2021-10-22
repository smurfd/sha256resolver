import ctypes
NUM = 16

fun = ctypes.CDLL("libcall_c.so") # Or full path to file
fun.myFunction.argtypes = [ctypes.c_int]

returnValue = fun.myFunction(NUM)
print(returnValue)
