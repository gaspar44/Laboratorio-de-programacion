/*
 * Comunitats.cpp
 *
 *  Created on: 2 dic. 2019
 *      Author: gaspar
 */
#include "Comunitat.h"
#include <math.h>

Comunitat::Comunitat(MatriuSparse* pMAdj) {
	m_sparseMatrix = pMAdj;
	calculaM2();
	calculaK();
	calculaA();
	creaIndexComs();
	m_firstActiveComunity = 0;
	creaDeltaQHeap();
}

void Comunitat::calculaA(){
	m_A.resize(m_k.size());

	for (int i = 0; i < m_k.size();i++){
		m_A[i] = double(m_k[i])/m_M2;
	}
}

void Comunitat::creaIndexComs(){
	int numberOfNodes = m_sparseMatrix->getNColumnes();
	m_indexOfActivaComunity.resize(numberOfNodes);

	for (int i = 0; i < numberOfNodes;i++){
		pair<int,int> pairOfPreviousAndNextComunity = make_pair(i - 1, i + 1);
		m_indexOfActivaComunity[i] = pairOfPreviousAndNextComunity;
	}
}

void Comunitat::creaDeltaQHeap(){
	if (m_M2 == 0)
		throw "Exception: M_2";

	m_sparseMatrix->creapMaps(m_deltaQ);

	double deltaQLeftSideOfMinusOperation = double(1) / m_M2;
	int powerM2 = pow(m_M2,2);

	for (int i = 0; i < m_deltaQ.size();i++){
		map<pair<int,int>,double> aux = m_deltaQ[i];
		map<pair<int,int>,double>::iterator mapIterator;
		double maxDeltaQInRow = 0;
		double newDeltaQ = 0;
		pair<int,int> keyofMaxDeltaQ;

		for (mapIterator = aux.begin();mapIterator != aux.end();++mapIterator){

			pair<int,int> key = make_pair(mapIterator->first.first, mapIterator->first.second);
			double deltaQRightSideOfMinusOperation = m_k[mapIterator->first.first] * m_k[mapIterator->first.second];
			deltaQRightSideOfMinusOperation = deltaQRightSideOfMinusOperation / powerM2;

			newDeltaQ = deltaQLeftSideOfMinusOperation - deltaQRightSideOfMinusOperation;
			mapIterator->second = newDeltaQ;

			if (newDeltaQ > maxDeltaQInRow){
				maxDeltaQInRow = newDeltaQ;
				keyofMaxDeltaQ = key;
			}
		}

		m_deltaQ[i] = aux;
		ElemHeap elementHeap = ElemHeap(maxDeltaQInRow,keyofMaxDeltaQ);
		m_hTotal.insert(elementHeap);
		pair<int,double> rowOfMaxDeltaQAndValue = make_pair(keyofMaxDeltaQ.first, maxDeltaQInRow);
		m_maxDeltaQOfRows.push_back(rowOfMaxDeltaQAndValue);
	}
}
