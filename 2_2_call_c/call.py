import ctypes
NUM = 16

fun = ctypes.CDLL("libmyfunc.so") # Or full path to file
fun.myFunction.argtypes = [ctypes.c_int]

returnValue = fun.myFunction(NUM)
print(returnValue)
