/*
 * Heap.cpp
 *
 *  Created on: 27 nov. 2019
 *      Author: gaspar
 */
#include "Heap.h"
#include <iostream>
#include <fstream>
using namespace std;

Heap::Heap(int maxElements){
	m_actualPosition = -1;
	m_maxNumberOfElementsInHeap = maxElements;
	m_data.resize(maxElements);
}

Heap::Heap(const Heap &h){
	m_actualPosition = h.m_actualPosition;
	m_data = h.m_data;
	m_index = h.m_index;
	m_maxNumberOfElementsInHeap = h.m_maxNumberOfElementsInHeap;
}

Heap& Heap::operator =(const Heap &h){
	m_actualPosition = h.m_actualPosition;
	m_data = h.m_data;
	m_index = h.m_index;
	m_maxNumberOfElementsInHeap = h.m_maxNumberOfElementsInHeap;
	return *this;
}

ostream& operator<<(ostream &out, const Heap &h){
	for (int i = 0; i > h.m_data.size();i++){
		out<<h.m_data[i].getVal()<<endl;
	}
	return out;
}

void Heap::insert(const ElemHeap &elementHeap){
	m_actualPosition++;
	if (m_actualPosition < m_maxNumberOfElementsInHeap){
		m_data[m_actualPosition] = elementHeap;
	}

	else {
		m_data.push_back(elementHeap);
		m_maxNumberOfElementsInHeap++;
	}


	int positionHelper = m_actualPosition;
	heapSort(positionHelper);
}

void Heap::resize(int newMaxValue){
	m_maxNumberOfElementsInHeap = newMaxValue;
	m_data.resize(m_maxNumberOfElementsInHeap);
}

void Heap::delMax(){
	if (m_actualPosition < 0)
		return;

	swapElementHeap(0, m_actualPosition);
	m_actualPosition--;
	descend(0);
}

void Heap::descend(int pos){
	int min = pos;
	int leftChild = getLefChild(pos);
	int rightChild = getRightChild(pos);

	if (leftChild <= m_maxNumberOfElementsInHeap && m_data[min] < m_data[leftChild]){
		min = leftChild;
	}

	if (rightChild <= m_maxNumberOfElementsInHeap && m_data[min] < m_data[rightChild]){
		min = rightChild;
	}

	if (min != pos){
		swapElementHeap(pos, min);
		descend(min);
	}
}

void Heap::modifElem(const ElemHeap& newValue){

}

void Heap::clear(){
	m_data.clear();
	m_actualPosition = -1;
}

bool Heap::operator ==(const Heap& h){
	if (m_maxNumberOfElementsInHeap != h.m_maxNumberOfElementsInHeap)
		return false;

	for (int i = 0; i < m_data.size();i++){
		if (!(m_data[i] == h.m_data[i]))
			return false;
	}

	return true;
}

void Heap::heapSort(int positionToStartSort){
	int father = getFather(positionToStartSort);
	int actual = positionToStartSort;

	while (actual != 0 && m_data[actual] > m_data[father]){
		swapElementHeap(actual, father);
		actual = father;
		father = getFather(father);
	}
}

void Heap::swapElementHeap(int actualNode,int fatherToSwitch) {
	ElemHeap helper = m_data[actualNode];
	m_data[actualNode] = m_data[fatherToSwitch];
	m_data[fatherToSwitch] = helper;
}

void Heap::ascend(int pos){
	int father = getFather(pos);
	while (pos != 0 && m_data[pos] > m_data[father]) {
		swapElementHeap(pos, father);
		pos = getFather(pos);
		father = getFather(pos);
	}
}
