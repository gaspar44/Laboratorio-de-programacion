#pragma once
#include "Heap.hpp"

template <class T>
class CuaPrioritat
{
public:
	CuaPrioritat() {}
	~CuaPrioritat() {}
	CuaPrioritat(const CuaPrioritat<T>& cua) {
		m_heap = cua.m_heap;
	}

	CuaPrioritat& operator=(const CuaPrioritat<T>& cua){
		m_heap = cua.m_heap;
		return *this;
	}

	bool esBuida() const {
		return m_heap.getMida() == -1;
	}

	int getNElements() const{
		return m_heap.getMida();
	}

	T& top(){
		return m_heap.getMinim();
	}

	void push(const T& element) {
		m_heap.insereix(element);
	}

	void pop(){
		m_heap.esborraMinim();
	}

	void remove(const T& element){
		m_heap.esborra(element);
	}

	void print() {
		m_heap.print();
	}

private:
	Heap<T> m_heap;
};
