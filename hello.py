from myntl import *

a = ZZ(5)
b = ZZ(10)
c = a + b
v = VecZZ()
v.SetLength(4, c)
print(v)