#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "ElemHeap.h"
using namespace std;

class Heap {
public:
	Heap() { m_actualPosition = -1; m_maxElement = 0; };
	Heap(int maxEls) { m_actualPosition = -1; m_maxElement = maxEls; m_data.resize(m_maxElement, ElemHeap()); m_index.resize(m_maxElement, -1);	};
	Heap(const Heap& h);
	~Heap() {};
	Heap& operator=(const Heap& h);

	ElemHeap& max() { return m_data[0]; }
	int size() { return m_actualPosition+1; }
	friend std::ostream& operator<<(std::ostream& out, const Heap& h);
	void insert(const ElemHeap& el);
	void resize(int mida) {	m_data.resize(mida, ElemHeap()); m_index.resize(mida, -1); m_maxElement = mida; m_actualPosition = -1;};
	void delMax();
	void delElem(int pos);
	void modifElem(const ElemHeap& nouVal);
	void clear();
	bool operator==(const Heap& h);

private:
	vector<ElemHeap> m_data;
	//Guardem els indexos del vei inicial per cada un dels valors que tenim guardats
	vector<int> m_index;
	int m_maxElement; //indica nombre total de nodes: array va de 0 a m_maxEls-1
	int m_actualPosition; //indica posicio ultima ocupada: inicialment -1

	int getFather(int pos) const { return ((pos - 1) / 2); }
	int getLeftSon(int pos) const  { return ((2 * pos) + 1); }
	int getRightSon(int pos) const { return ((2 * pos) + 2); }
	void swapPosition(int pos1, int pos2) { ElemHeap aux = m_data[pos1]; m_data[pos1] = m_data[pos2]; m_data[pos2] = aux;}

	std::ostream& printRec(std::ostream& out,int pos,int n) const;
	void ascend(int pos);
	void descend(int pos);
};
