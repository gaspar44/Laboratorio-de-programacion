#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

void ordenaArray(vector<int>& v, int indexInici, int indexFinal){
	if (v.size() == 0 || v.size() == 1 || indexInici == indexFinal)
		return;

	int index;
	int indexOfMinElement = 0;
	int minElement = v[indexInici];
	for(index = indexInici; index <= indexFinal; index++){
		if (v[index] < minElement){
			minElement = v[index];
			indexOfMinElement = index;
		}
	}

	if (indexOfMinElement != 0 ){
		swap(v[indexInici],v[indexOfMinElement]);
	}

	return ordenaArray(v, indexInici + 1, indexFinal);
}
