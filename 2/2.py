import ctypes
from ctypes import *

so_file = '/Users/adityaved/prj_ws/python_c_integration/2/call_c.so'
call_c = CDLL(so_file)
# call_c.getArray.restype = ctypes.POINTER(ctypes.c_int)
# my_list = call_c.getArray()
call_c.main(16)
