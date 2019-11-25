#include "MatriuSparse.h"

int main() {
	string fileName = "XarxaCom.txt";
	MatriuSparse ms = MatriuSparse(fileName);
	vector<map<pair<int,int>,float>> vMaps;
	ms.creapMaps(vMaps);
	map<pair<int,int>,float>::iterator it;

//	for (int i = 0;i < vMaps.size();i++){
//		cout<<vMaps[i].size()<<endl;
//		for (it = vMaps[i].begin(); it != vMaps[i].end(); ++it){
//			cout<<it->second;
//			cout<<endl;
//		}
//	}

	return 0;
}
