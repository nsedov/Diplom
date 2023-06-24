from myntl import Mat_ZZ, ZZ
m = Mat_ZZ()
m.SetDims(2, 2)
n = Mat_ZZ()
n.SetDims(2, 2)
n[0, 0] = ZZ(2)
nw = ZZ(3)
m[0, 0] = nw
b = m + n
print(b)