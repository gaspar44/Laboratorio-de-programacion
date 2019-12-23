/*
 * Comunitats.cpp
 *
 *  Created on: 2 dic. 2019
 *      Author: gaspar
 */
#include "Comunitat.h"
#include <math.h>
#include <algorithm>

Comunitat::Comunitat(MatriuSparse* pMAdj) {
	m_sparseMatrix = pMAdj;
	m_firstActiveComunity = 0;
	m_Q = 0;

	InicialitzaDendrograms();
	calculaM2();
	calculaK();
	calculaA();

	creaDeltaQHeap();
	creaIndexComs();
}

void Comunitat::calculaA(){
	m_A.resize(m_k.size());

	for (int i = 0; i < m_k.size();i++){
		m_A[i] = double(m_k[i])/m_M2;
	}
}

void Comunitat::creaIndexComs(){
	int numberOfNodes = m_sparseMatrix->getNColumnes();
	m_indexOfActiveComunity.resize(numberOfNodes);

	for (int i = 0; i < numberOfNodes;i++){
		pair<int,int> pairOfPreviousAndNextComunity = make_pair(i - 1, i + 1);
		m_indexOfActiveComunity[i] = pairOfPreviousAndNextComunity;
	}
}

void Comunitat::creaDeltaQHeap(){
	if (m_M2 == 0)
		throw "Exception: M_2";

	m_sparseMatrix->creapMaps(m_deltaQ);

	for (int i = 0; i < m_deltaQ.size();i++){
		map<pair<int,int>,double> aux = m_deltaQ[i];
		map<pair<int,int>,double>::iterator mapIterator;
		double maxDeltaQInRow = 0;
		pair<int,int> keyofMaxDeltaQ;

		getMaxDeltaQ(aux, maxDeltaQInRow, keyofMaxDeltaQ);

		m_deltaQ[i] = aux;
		ElemHeap elementHeap = ElemHeap(maxDeltaQInRow,keyofMaxDeltaQ);
		m_hTotal.insert(elementHeap);
		pair<int,double> rowOfMaxDeltaQAndValue = make_pair(keyofMaxDeltaQ.first, maxDeltaQInRow);
		m_maxDeltaQOfRows.push_back(rowOfMaxDeltaQAndValue);
	}
}

void Comunitat::getMaxDeltaQ(map<pair<int,int>,double> &aux, double &maxDeltaQInRow,pair<int,int> &keyOfMaxDeltaQ){
	map<pair<int,int>,double>::iterator mapIterator;
	double deltaQLeftSideOfMinusOperation = double(1) / m_M2;
	int powerM2 = pow(m_M2,2);
	double newDeltaQ = 0;

	for (mapIterator = aux.begin();mapIterator != aux.end();++mapIterator){

		pair<int,int> key = make_pair(mapIterator->first.first, mapIterator->first.second);
		double deltaQRightSideOfMinusOperation = m_k[mapIterator->first.first] * m_k[mapIterator->first.second];
		deltaQRightSideOfMinusOperation = deltaQRightSideOfMinusOperation / powerM2;

		newDeltaQ = deltaQLeftSideOfMinusOperation - deltaQRightSideOfMinusOperation;
		mapIterator->second = newDeltaQ;

		if (newDeltaQ > maxDeltaQInRow){
			maxDeltaQInRow = newDeltaQ;
			keyOfMaxDeltaQ = key;
		}
	}
}

void Comunitat::calculaComunitats(list<Tree<double>*>& listDendrogram){
	bool done = false; // deltaQ > 0

//	while(!done){
		ElemHeap maxElement = m_hTotal.max();
		m_hTotal.delMax();
		pair<int,int> comunitiesToFusion = maxElement.getPos();
//		m_indexOfActiveComunity.get
		fusiona(comunitiesToFusion.first,comunitiesToFusion.second);

		deleteAbsorbedComunityFromActiveComunities(comunitiesToFusion.first);
		m_A[comunitiesToFusion.first] = m_A[comunitiesToFusion.first] + m_A[comunitiesToFusion.second];
		m_Q+= maxElement.getVal();

//		m_indexOfActiveComunity[comunitiesToFusion.first] = 0;
//	}
}

void Comunitat::deleteAbsorbedComunityFromActiveComunities(int comunityToBeAbsorbed){
	m_indexOfActiveComunity[m_indexOfActiveComunity[comunityToBeAbsorbed].first].second = m_indexOfActiveComunity[comunityToBeAbsorbed].second;
	m_indexOfActiveComunity[m_indexOfActiveComunity[comunityToBeAbsorbed].second].first = m_indexOfActiveComunity[comunityToBeAbsorbed].first;

	m_firstActiveComunity = m_firstActiveComunity == comunityToBeAbsorbed ? m_hTotal.max().getPos().first : m_firstActiveComunity;

}

void Comunitat::fusiona(int comunityToBeAbsorbed, int comunityToKeepAsFusionOfBoth){
	vector<int> neighboursOfTheComunityToBeAbsorbed = getNeighbourds(comunityToBeAbsorbed);
	vector<int> neighboursOfTheComunityWhoAbsorbs = getNeighbourds(comunityToKeepAsFusionOfBoth);

	commonNeighbourdsOfFusion(comunityToBeAbsorbed,comunityToKeepAsFusionOfBoth,
			neighboursOfTheComunityToBeAbsorbed,
			neighboursOfTheComunityWhoAbsorbs);


	recalculateDeltaQOfNeighbourdsOfCommunityToBeAbsorbed(comunityToBeAbsorbed,comunityToKeepAsFusionOfBoth, neighboursOfTheComunityToBeAbsorbed);
	recalculateDeltaQOfNeighbourdsOfCommunityWhoAbsorbs(comunityToBeAbsorbed, comunityToKeepAsFusionOfBoth, neighboursOfTheComunityWhoAbsorbs);
	// Recalcula maxDeltaQ en caso de hacer falta.

	m_deltaQ[comunityToBeAbsorbed].clear();
	m_deltaQ[comunityToKeepAsFusionOfBoth].erase(make_pair(comunityToKeepAsFusionOfBoth, comunityToBeAbsorbed));
}

vector<int> Comunitat::getNeighbourds(int comunityToGetNeighbourds){
	vector<int> neighbours;
	map<pair<int,int>,double> auxOfComunityToGetNeighbours = m_deltaQ[comunityToGetNeighbourds];
	map<pair<int,int>,double>::iterator aux;

	for(aux = auxOfComunityToGetNeighbours.begin(); aux != auxOfComunityToGetNeighbours.end();++aux){
		neighbours.push_back(aux->first.second);
	}

	return neighbours;
}

void Comunitat::commonNeighbourdsOfFusion(int comunityToBeAbsorbed, int comunityToKeepAsFusionOfBoth,vector<int> &neighboursOfTheComunityToBeAbsorbed,vector<int> &neighboursOfTheComunityWhoAbsorbs){
	sort(neighboursOfTheComunityToBeAbsorbed.begin(),neighboursOfTheComunityToBeAbsorbed.end());
	sort(neighboursOfTheComunityWhoAbsorbs.begin(),neighboursOfTheComunityWhoAbsorbs.end());

	vector<int> commonNeighbours(neighboursOfTheComunityToBeAbsorbed.size() + neighboursOfTheComunityWhoAbsorbs.size());
	vector<int>::iterator lastElement,iter;

	lastElement = set_intersection(neighboursOfTheComunityToBeAbsorbed.begin(),neighboursOfTheComunityToBeAbsorbed.end(),
			neighboursOfTheComunityWhoAbsorbs.begin(),neighboursOfTheComunityWhoAbsorbs.end(),
			commonNeighbours.begin());

	vector<int> neighbourdsOfComunityToBeAborbedWithNoCommon;
	vector<int> neighbourdsOfComunityWhoAbsordsWithNoCommon;
	for (auto iter = commonNeighbours.begin(); iter != lastElement;++iter){
		for (int j = 0; j < neighboursOfTheComunityToBeAbsorbed.size();j++){
			if (*iter != neighboursOfTheComunityToBeAbsorbed[j]){
				neighbourdsOfComunityToBeAborbedWithNoCommon.push_back(neighboursOfTheComunityToBeAbsorbed[j]);
			}
		}
	}

	for (auto iter = commonNeighbours.begin(); iter != lastElement;++iter){
		for (int j = 0; j < neighboursOfTheComunityWhoAbsorbs.size();j++){
			if (*iter != neighboursOfTheComunityWhoAbsorbs[j]){
				neighbourdsOfComunityWhoAbsordsWithNoCommon.push_back(neighboursOfTheComunityWhoAbsorbs[j]);
			}
		}
	}

	neighboursOfTheComunityToBeAbsorbed.clear();
	neighboursOfTheComunityToBeAbsorbed = neighbourdsOfComunityToBeAborbedWithNoCommon;
	neighboursOfTheComunityWhoAbsorbs.clear();
	neighboursOfTheComunityWhoAbsorbs = neighbourdsOfComunityWhoAbsordsWithNoCommon;

	map<pair<int,int>,double> mapOfComunityToKeepAsFusion = m_deltaQ[comunityToKeepAsFusionOfBoth];
	for (iter = commonNeighbours.begin(); iter != lastElement; ++iter){
		map<pair<int,int>,double> mapOfNeighbourds = m_deltaQ[*iter];

		pair<int,int> keyToSearch1 = make_pair(*iter, comunityToBeAbsorbed);
		pair<int,int> keyToSearch2 = make_pair(*iter,comunityToKeepAsFusionOfBoth);
		pair<int,int> keyToSearch3 = make_pair(comunityToKeepAsFusionOfBoth,*iter);
		pair<int,int> keyToSearch4 = make_pair(comunityToBeAbsorbed,*iter);

		mapOfNeighbourds[keyToSearch2] = mapOfNeighbourds[keyToSearch2] + mapOfNeighbourds[keyToSearch1];
		mapOfNeighbourds.erase(keyToSearch1);

		if (mapOfNeighbourds.find(keyToSearch4) != mapOfNeighbourds.end()){
			mapOfComunityToKeepAsFusion[keyToSearch3] = mapOfComunityToKeepAsFusion[keyToSearch3] + mapOfNeighbourds[keyToSearch4];
		}
		m_deltaQ[*iter] = mapOfNeighbourds;
	}

	m_deltaQ[comunityToKeepAsFusionOfBoth] = mapOfComunityToKeepAsFusion;

}

void Comunitat::recalculateDeltaQOfNeighbourdsOfCommunityToBeAbsorbed(int comunityToBeAbsorbed,int comunityToKeepAsFusionOfBoth, vector<int> &neighboursOfTheComunityToBeAbsorbed){
	pair<int,int> pairOfComunityToKeep = make_pair(comunityToKeepAsFusionOfBoth, comunityToKeepAsFusionOfBoth);
	map<pair<int,int>,double> mapOfComunityToKeepAsFusion = m_deltaQ[comunityToKeepAsFusionOfBoth];

	for (int i = 0; i < neighboursOfTheComunityToBeAbsorbed.size();i++){
		int actualNeighbourd = neighboursOfTheComunityToBeAbsorbed[i];
		map<pair<int,int>,double> mapOfNeighbourds = m_deltaQ[actualNeighbourd];

		pair<int,int> keyToSearch1 = make_pair(actualNeighbourd,comunityToKeepAsFusionOfBoth);
		pair<int,int> keyToSearch2 = make_pair(actualNeighbourd, comunityToBeAbsorbed);
		pair<int,int> keyToSearch3 = make_pair(comunityToKeepAsFusionOfBoth,actualNeighbourd);
		pair<int,int> keyToSearch4 = make_pair(comunityToBeAbsorbed,actualNeighbourd);

		double rightSideOperand = 2 * m_A[comunityToKeepAsFusionOfBoth] * m_A[actualNeighbourd];

		if (pairOfComunityToKeep != keyToSearch1 && pairOfComunityToKeep != keyToSearch3){
			mapOfNeighbourds[keyToSearch1] = mapOfNeighbourds[keyToSearch2] - rightSideOperand;
			mapOfNeighbourds.erase(keyToSearch2);
			mapOfComunityToKeepAsFusion[keyToSearch3] = mapOfNeighbourds[keyToSearch4] - rightSideOperand;
			m_deltaQ[actualNeighbourd] = mapOfNeighbourds;
		}
	}

	m_deltaQ[comunityToKeepAsFusionOfBoth] = mapOfComunityToKeepAsFusion;
}

void Comunitat::recalculateDeltaQOfNeighbourdsOfCommunityWhoAbsorbs(int comunityToBeAbsorbed,int comunityToKeepAsFusionOfBoth, vector<int> &neighboursOfTheComunityWhoAbsorbs){
	map<pair<int,int>,double> mapOfComunityToKeepAsFusion = m_deltaQ[comunityToKeepAsFusionOfBoth];
	for (int i = 0; i < neighboursOfTheComunityWhoAbsorbs.size();i++){
		int actualNeighbourd = neighboursOfTheComunityWhoAbsorbs[i];

		if (actualNeighbourd != comunityToBeAbsorbed){
			map<pair<int,int>,double> mapOfNeighbourds = m_deltaQ[actualNeighbourd];

			pair<int,int> keyToSearch1 = make_pair(actualNeighbourd,comunityToKeepAsFusionOfBoth);
			pair<int,int> keyToSearch2 = make_pair(comunityToKeepAsFusionOfBoth,actualNeighbourd);

			double rightSideOperand = 2 * m_A[comunityToKeepAsFusionOfBoth] * m_A[actualNeighbourd];

			mapOfNeighbourds[keyToSearch1] = mapOfNeighbourds[keyToSearch1] - rightSideOperand;
			mapOfComunityToKeepAsFusion[keyToSearch2] = mapOfComunityToKeepAsFusion[keyToSearch2] - rightSideOperand;
			m_deltaQ[actualNeighbourd] = mapOfNeighbourds;
		}
	}

	m_deltaQ[comunityToKeepAsFusionOfBoth] = mapOfComunityToKeepAsFusion;
}
