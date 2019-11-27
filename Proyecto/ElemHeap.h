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

	ElemHeap() { m_Val = 0; m_Pos = { 0, 0 }; }
	ElemHeap(double val, std::pair<int, int> pos) { m_Val = val; m_Pos = pos; };
	double getVal() const { return m_Val; }
	std::pair<int,int> getPos() const { return m_Pos; }
	bool operator<(const ElemHeap& e) { return (m_Val < e.m_Val); }
	bool operator<=(const ElemHeap& e) { return (m_Val <= e.m_Val); }
	bool operator>(const ElemHeap& e) { return (m_Val > e.m_Val);}
	bool operator>=(const ElemHeap& e) { return (m_Val >= e.m_Val); }
	bool operator==(const ElemHeap& e) { return ( m_Val == e.m_Val); }
	~ElemHeap() {};
	ElemHeap& operator=(const ElemHeap& e){
		m_Val = e.m_Val;
		m_Pos = e.m_Pos;
		return *this;
	};
	friend std::ostream& operator<<(std::ostream& out, const ElemHeap& elHeap);

private:
	double m_Val;
	std::pair<int, int> m_Pos;
};


#endif /* ELEMHEAP_H_ */
