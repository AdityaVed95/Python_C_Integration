import ctypes
from ctypes import *

so_file = '/Users/adityaved/prj_ws/python_c_integration/4/call_c.so'
call_c = CDLL(so_file)

call_c.do_conversion.restype = ctypes.POINTER(ctypes.c_int)
number = 7
size_of_input = 20

result_array = call_c.do_conversion(number, size_of_input)

print(result_array)

python_list = []

for i in range(size_of_input):
    python_list.append(result_array[i])

print(python_list)
call_c.free_array(result_array)



