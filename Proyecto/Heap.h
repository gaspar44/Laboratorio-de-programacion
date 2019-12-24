/*
 * Heap.h
 *
 *  Created on: 27 nov. 2019
 *      Author: gaspar
 */

#ifndef HEAP_H_
#define HEAP_H_
#include <ostream>
#include <vector>
#include <iostream>
#include "ElemHeap.h"

class Heap {
	public:
	Heap() : m_actualPosition(-1), m_maxNumberOfElementsInHeap(0) {}
	Heap(int maxEls);
	Heap(const Heap& h);
	~Heap() {};
	Heap& operator=(const Heap& h);
	ElemHeap& max() { return m_data[0]; }
	int size() { return m_actualPosition; }
	friend std::ostream& operator<<(std::ostream& out, const Heap& h){
		if (h.m_actualPosition == -1){
			out<<"empty Tree"<<std::endl;
			return out;
		}

		for(int i = 0; i <= h.m_actualPosition;i++){
			out<<h.m_data[i]<<std::endl;
		}
		return out;
	}
	void insert(const ElemHeap& el);
	void resize(int mida);
	void modifElem(int communityToTryToChange,const ElemHeap& newValue);
	void delMax();
	void delElem(int pos);
	void modifElem(const ElemHeap& nouVal);
	void clear();
	bool operator==(const Heap& h);

private:

	std::vector<ElemHeap> m_data;
	int m_maxPosibleValue = 9999;
	//Guardem indexs del vei inicial per cada un dels valors que tenim guardats
	std::vector<int> m_index;
	int m_maxNumberOfElementsInHeap; //indica nombre total de nodes: array va de 0 a m_maxEls‐1
	int m_actualPosition; //indica posicio ultima ocupada: inicialment ‐1

	int getFather(int pos) const { return ((pos - 1) / 2); }
	int getLefChild(int pos) const { return ((2 * pos) + 1); }
	int getRightChild(int pos) const { return ((2 * pos) + 2); }
	void swapElementHeap(int pos1, int pos2);
	std::ostream& printRec(std::ostream& out,int pos,int n) const;
	void ascend(int pos);
	void descend(int pos);
	void heapSort(int positionToStartSort);

};


#endif /* HEAP_H_ */
