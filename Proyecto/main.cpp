#include "MatriuSparse.h"
#include "Heap.h"
#include "Comunitat.h"
#include <stdio.h>
#include <algorithm>

void print(Comunitat comunity){
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
}

int main() {
	MatriuSparse *sparseMatrix = new MatriuSparse("XarxaCom.txt");
	vector<map<pair<int,int>,double>> vMap;
	Comunitat comunity = Comunitat(sparseMatrix);

	list<Tree<double>*> dendograms;
	comunity.calculaComunitats(dendograms);
	print(comunity);
	comunity.printTree();

	return 0;
}
