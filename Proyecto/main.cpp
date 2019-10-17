#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "SparseMatrix.h"
using namespace std;

int main () {
	SparseMatrix m = SparseMatrix("Xarxa1.txt");
	SparseMatrix m2 = SparseMatrix(m);
	m2 = m2*2;
	vector<float> v = {2,1,3,4,5,6,7,8};
	vector<float> prueba = m * v;

	for(int i = 0 ; i < 8;i++){
		cout<<prueba.at(i)<<endl;
	}

  return 0;
}
