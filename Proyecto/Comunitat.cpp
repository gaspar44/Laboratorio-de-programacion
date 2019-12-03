/*
 * Comunitats.cpp
 *
 *  Created on: 2 dic. 2019
 *      Author: gaspar
 */
#include "Comunitat.h"

Comunitat::Comunitat(MatriuSparse* pMAdj) {
	m_sparseMatrix = pMAdj;
	m_primComdeltaQ = 0;
	calculaM2();
	calculaK();
	calculaA();
}

void Comunitat::calculaA(){
	m_A.resize(m_k.size());

	for (int i = 0; i < m_k.size();i++){
		m_A[i] = m_k[i]/m_M2;
	}
}

void Comunitat::creaIndexComs(){

}

void Comunitat::creaDeltaQHeap(){
	double deltaQLeftSideOfMinusOperation = 1 / m_M2;

	for (int i = 0; i < m_deltaQ.size();i++){
		map<pair<int,int>,double> aux = m_deltaQ[i];
		map<pair<int,int>,double>::iterator mapIterator;
		double maxDeltaQInRow = 0;
		pair<int,int> keyofMaxDeltaQ;

		for (mapIterator = aux.begin();mapIterator != aux.end();++mapIterator){
			pair<int,int> key = make_pair(mapIterator->first.first, mapIterator->first.second);
			double newDeltaQ = deltaQLeftSideOfMinusOperation - (( mapIterator->first.first * mapIterator->first.second)/(m_M2 * m_M2));
			mapIterator->second = newDeltaQ;

			if (newDeltaQ > maxDeltaQInRow){
				maxDeltaQInRow = newDeltaQ;
				keyofMaxDeltaQ = key;
			}
		}

		ElemHeap elementHeap = ElemHeap(maxDeltaQInRow,keyofMaxDeltaQ);
		m_hTotal.insert(elementHeap);

		/* Se debe de hacer uso del vector de maxDeltaQ, para así evitar calculos innecesarios en el futuro, y se guarda usando
		* la fila y el valor hallado
		*/
	}
}
