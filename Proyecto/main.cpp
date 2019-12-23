#include "MatriuSparse.h"
#include "Heap.h"
#include "Comunitat.h"
#include <stdio.h>
#include <algorithm>

int main() {
	MatriuSparse *sparseMatrix = new MatriuSparse("XarxaCom.txt");
	vector<map<pair<int,int>,double>> vMap;
	Comunitat comunity = Comunitat(sparseMatrix);
	comunity.printTree();


	list<Tree<double>*> dendograms;
	comunity.calculaComunitats(dendograms);
	vector<map<pair<int, int>, double>>  deltaQ = comunity.getdeltaQ();

	for (int i = 0; i < deltaQ.size();i++){
		map<pair<int,int>,double> aux = deltaQ[i];
		map<pair<int,int>,double>::iterator mapIterator;
		pair<int,int> keyofMaxDeltaQ;

		for (mapIterator = aux.begin();mapIterator != aux.end();++mapIterator){
			cout<<"fila: "<<mapIterator->first.first<<", columna: "<<mapIterator->first.second;
			printf(" valor: %lf\n",mapIterator->second);
		}
	cout<<endl;
	}


//	vector<int> a = {1, 2, 3, 5};
//	vector<int> b = {3, 5, 10};
//
//	vector <int> c(a.size() + b.size());
//
//	vector<int>::iterator it, st;
//	it = set_intersection(a.begin(),a.end(),b.begin(),b.end(),c.begin());
//
//    for (st = c.begin(); st != it; ++st)
//        cout << *st <<endl;

	return 0;
}
