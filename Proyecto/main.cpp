#include "MatriuSparse.h"

int main() {
	string fileName = "XarxaCom.txt";
	MatriuSparse ms = MatriuSparse(fileName);
	vector<Tree<double>*> dendogram;
	ms.calculaDendograms(dendogram);

	for (int i = 0; i < dendogram.size();i++){
		cout<<i<<" : "<<dendogram[i]->getData()<<endl;
	}

	return 0;
}
