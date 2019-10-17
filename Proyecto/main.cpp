#include <iostream>
#include <string>
#include <map>

#include "SparseMatrix.h"
using namespace std;

int main () {
	SparseMatrix m = SparseMatrix("Xarxa1.txt");
	cout<<m;

  return 0;
}
