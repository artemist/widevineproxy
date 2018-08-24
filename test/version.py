import ctypes
c = ctypes.CDLL("../cmake-build-debug/libwidevineproxy.so")
print(c.GetCdmVersion())
