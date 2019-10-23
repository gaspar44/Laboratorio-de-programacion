#include <list>
using namespace std;

int maxElement(int* array,int n) {
    if (n == 1)
        return array[0];

    return max(array[n-1],maxElement(array,n-1));
}


int MaxElementsLlista(list<int> &l){
	if (l.size() == 0 )
		return 0;

    int array[l.size()];
	list<int>::iterator it;
	int size = 0;
	for (it = l.begin(); it !=l.end();++it){
		array[size] = *it;
		size++;
	}
	return maxElement(array,size);
}
