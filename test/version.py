import ctypes
c = ctypes.CDLL("../cmake-build-debug/libwidevineproxy.so")
c.GetCdmVersion.argtypes = []
c.GetCdmVersion.restype = ctypes.c_char_p
print(c.GetCdmVersion())
