/*
 * ElemHeap.h
 *
 *  Created on: 27 nov. 2019
 *      Author: gaspar
 */

#ifndef ELEMHEAP_H_
#define ELEMHEAP_H_
#include <fstream>

class ElemHeap {
public:

	ElemHeap() { m_value = 0; m_position = { 0, 0 }; }
	ElemHeap(double val, std::pair<int, int> pos) { m_value = val; m_position = pos; };
	ElemHeap(double value) { m_value = value ; m_position = {0 ,0}; };
	double getVal() const { return m_value; }
	std::pair<int,int> getPos() const { return m_position; }
	bool operator<(const ElemHeap& e) { return (m_value < e.m_value); }
	bool operator<=(const ElemHeap& e) { return (m_value <= e.m_value); }
	bool operator>(const ElemHeap& e) { return (m_value > e.m_value);}
	bool operator>=(const ElemHeap& e) { return (m_value >= e.m_value); }
	bool operator==(const ElemHeap& e) { return ( m_value == e.m_value); }
	void setValor(double value) { m_value = value; } ;
	~ElemHeap() {};
	ElemHeap& operator=(const ElemHeap& e){
		m_value = e.m_value;
		m_position = e.m_position;
		return *this;
	};
	friend std::ostream& operator<<(std::ostream& out, const ElemHeap& elHeap) {
		out<< "( < "<<elHeap.m_position.first<<" , "<<elHeap.m_position.second<<" > ; "<<elHeap.m_value<<" )";
		return out;
	}

private:
	double m_value;
	std::pair<int, int> m_position;
};


#endif /* ELEMHEAP_H_ */
