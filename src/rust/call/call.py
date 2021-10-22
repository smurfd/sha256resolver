#import ctypes

#fun = ctypes.CDLL("rust2py.so") # Or full path to file
#fun.myFunction.argtypes = [ctypes.sum_as_string]

#print(fun.sum_as_string(12, 234))
import rust2py
#print(rust2py.__doc__)
print(rust2py.sum_as_string(12,234))
