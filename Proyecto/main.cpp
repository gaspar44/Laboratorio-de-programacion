#include "MatriuSparse.h"
#include "Heap.h"
#include "Comunitat.h"

int main() {
	MatriuSparse *sparseMatrix = new MatriuSparse("XarxaCom.txt");
	vector<map<pair<int,int>,double>> vMap;
	Comunitat comunity = Comunitat(sparseMatrix);
	//cout<<sparseMatrix->getNValues()<<endl;
	return 0;
}
