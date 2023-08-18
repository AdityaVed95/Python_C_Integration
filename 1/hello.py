from ctypes import *

so_file = '/Users/adityaved/prj_ws/python_c_integration/1/my_functions.so'
my_functions = CDLL(so_file)
print(my_functions)
print(my_functions.square_calc(10))
