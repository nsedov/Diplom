#include <NTL/ZZ.h>
#include <iostream>
#include <NTL/vector.h>
#include <NTL/matrix.h>
#include <vector>

using namespace NTL;
using namespace std;

int main() {
	Mat<ZZ> a;
	ZZ b(5);
	a.SetDims(2, 2);
	a.put(0, 0, b);
	//a[0][0] = 1;
	cout << a << endl;
	return 0;
}