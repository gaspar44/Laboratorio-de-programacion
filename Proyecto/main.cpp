#include <iostream>
#include <string>
#include <map>

#include "SparseMatrix.h"
using namespace std;

int main () {
	SparseMatrix m = SparseMatrix("Xarxa1.txt");
	SparseMatrix m2 = SparseMatrix(m);
	m2 = m2*2;
	cout<<m2;

  return 0;
}
