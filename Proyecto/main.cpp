#include "MatriuSparse.h"
#include "Heap.h"

int main() {
	vector<ElemHeap> elementHeaps = {
			ElemHeap(4,{1,2}),
			ElemHeap(3,{0,0}),
			ElemHeap(5,{4,5}),
			ElemHeap(15,{7,6}),
			ElemHeap(24,{4,7}),
			ElemHeap(39,{3,2}),
			ElemHeap(37,{3,1})
	};

	Heap heap = Heap();
	for (int i = 0; i < elementHeaps.size();i++){
		heap.insert(elementHeaps[i]);
	}

	return 0;
}
