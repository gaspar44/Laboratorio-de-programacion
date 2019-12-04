/*
 * Comunitats.h
 *
 *  Created on: 2 dic. 2019
 *      Author: gaspar
 */

#ifndef COMUNITAT_H_
#define COMUNITAT_H_
#include <list>
#include <vector>
#include "MatriuSparse.h"
#include "Tree.h"
#include "Heap.h"

class Comunitat {
public:
	Comunitat(MatriuSparse* pMAdj);
	~Comunitat() {};

	void calculaM2() { m_M2 = m_sparseMatrix->getNValues(); };
	void calculaK() { m_sparseMatrix->calculaGrau(m_k); };
	void calculaA();
	void creaDeltaQHeap();
	void creaIndexComs();
	void InicialitzaDendrograms() { m_sparseMatrix->calculaDendograms(m_vDendrograms); };
	void calculaComunitats(list<Tree<double>*>& listDendrogram);
	void fusiona(int com1, int com2);
	void modificaVei(int com1, int com2, int vei, int cas);
	int getM2() { return m_M2; }

	vector<int> getK() { return m_k; }
	vector<double> getA() { return m_A; }
	vector<map<pair<int, int>, double>> getdeltaQ() { return m_deltaQ;}
	Heap gethTotal() { return m_hTotal;}
	vector<pair<int, int>> getIndexComs() { return m_indexOfActivaComunity; }
	void clear();

private:
	MatriuSparse* m_sparseMatrix;
	Heap m_hTotal;
	double m_Q;
	int m_M2;
	int m_firstActiveComunity;

	vector<map<pair<int, int>, double>> m_deltaQ;
	vector<pair<int, int>> m_indexOfActivaComunity;
	vector<pair<int, double>> m_maxDeltaQOfRows;
	vector<int> m_k;
	vector<double> m_A;
	vector<Tree<double>*> m_vDendrograms;
};

#endif /* COMUNITATS_H_ */
