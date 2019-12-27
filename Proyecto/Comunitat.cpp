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

Comunitat::Comunitat(const Comunitat& community){
	m_sparseMatrix = community.m_sparseMatrix;
	m_Q = community.m_Q;
	m_hTotal = community.m_hTotal;
	m_M2 = community.m_M2;
	m_firstActiveComunity = community.m_firstActiveComunity;

	for (int i = 0;i < community.m_deltaQ.size();i++){
		m_deltaQ.push_back(community.m_deltaQ[i]);
	}

	for (int i = 0; i < community.m_indexOfActiveComunity.size();i++){
		m_indexOfActiveComunity.push_back(community.m_indexOfActiveComunity[i]);
	}

	for (int i = 0; i < community.m_maxDeltaQOfRows.size();i++){
		m_maxDeltaQOfRows.push_back(community.m_maxDeltaQOfRows[i]);
	}

	for (int i = 0; i < community.m_vDendrograms.size();i++){
		m_vDendrograms.push_back(community.m_vDendrograms[i]);
	}

	for (int i = 0; i < community.m_candidatesElementsToModificateInMaxHeap.size();i++){
		m_candidatesElementsToModificateInMaxHeap.push_back(community.m_candidatesElementsToModificateInMaxHeap[i]);
	}
}

Comunitat& Comunitat::operator =(const Comunitat &community){
	m_sparseMatrix = community.m_sparseMatrix;
	m_Q = community.m_Q;
	m_hTotal = community.m_hTotal;
	m_M2 = community.m_M2;
	m_firstActiveComunity = community.m_firstActiveComunity;

	for (int i = 0;i < community.m_deltaQ.size();i++){
		m_deltaQ.push_back(community.m_deltaQ[i]);
	}

	for (int i = 0; i < community.m_indexOfActiveComunity.size();i++){
		m_indexOfActiveComunity.push_back(community.m_indexOfActiveComunity[i]);
	}

	for (int i = 0; i < community.m_maxDeltaQOfRows.size();i++){
		m_maxDeltaQOfRows.push_back(community.m_maxDeltaQOfRows[i]);
	}

	for (int i = 0; i < community.m_vDendrograms.size();i++){
		m_vDendrograms.push_back(community.m_vDendrograms[i]);
	}

	for (int i = 0; i < community.m_candidatesElementsToModificateInMaxHeap.size();i++){
		m_candidatesElementsToModificateInMaxHeap.push_back(community.m_candidatesElementsToModificateInMaxHeap[i]);
	}

	return *this;
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
	m_hTotal.resize(m_sparseMatrix->getNColumnes());

	for (int i = 0; i < m_deltaQ.size();i++){
		map<pair<int,int>,double> aux = m_deltaQ[i];
		map<pair<int,int>,double>::iterator mapIterator;
		double maxDeltaQInRow = 0;
		pair<int,int> keyofMaxDeltaQ;

		getMaxDeltaQ(aux, maxDeltaQInRow, keyofMaxDeltaQ);

		m_deltaQ[i] = aux;
		ElemHeap elementHeap = ElemHeap(maxDeltaQInRow,keyofMaxDeltaQ);
		pair<int,double> rowOfMaxDeltaQAndValue = make_pair(keyofMaxDeltaQ.second, maxDeltaQInRow);
		m_hTotal.insert(elementHeap);
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
	ElemHeap maxElement = m_hTotal.max();

	while(maxElement.getVal() != 0 && m_hTotal.size() != 0){
		printTree();
		maxElement = m_hTotal.max();
		m_hTotal.delMax();
		pair<int,int> comunitiesToFusion = maxElement.getPos();
		int communityToBeAbsorbed = comunitiesToFusion.first;
		int communitiyToKeepAsFusionOfBoth = comunitiesToFusion.second;
		fusiona(communityToBeAbsorbed,communitiyToKeepAsFusionOfBoth);
		fixMaxHeapAfterFusion(communitiyToKeepAsFusionOfBoth,communityToBeAbsorbed);
		m_A[communitiyToKeepAsFusionOfBoth] = m_A[communityToBeAbsorbed] + m_A[communitiyToKeepAsFusionOfBoth];
		m_Q += maxElement.getVal();
		updateDendogram(communitiyToKeepAsFusionOfBoth,communityToBeAbsorbed);
	}

	for (int i = 0; i < m_vDendrograms.size();i++){
		if (m_vDendrograms[i] != nullptr){
			listDendrogram.push_back(m_vDendrograms[i]);
		}
	}
}

void Comunitat::updateDendogram(int communitiyToKeepAsFusionOfBoth,int communityToBeAbsorbed){
	Tree<double> *treeWithDeltaQAndCommunitiesWhoGenerate = new Tree<double>(m_Q);
	treeWithDeltaQAndCommunitiesWhoGenerate->setLeft(m_vDendrograms[communitiyToKeepAsFusionOfBoth]);
	treeWithDeltaQAndCommunitiesWhoGenerate->setRight(m_vDendrograms[communityToBeAbsorbed]);
	m_vDendrograms[communityToBeAbsorbed] = nullptr;
	m_vDendrograms[communitiyToKeepAsFusionOfBoth] = treeWithDeltaQAndCommunitiesWhoGenerate;
}

void Comunitat::deleteAbsorbedComunityFromActiveCommunities(int comunityToBeAbsorbed){
	m_indexOfActiveComunity[m_indexOfActiveComunity[comunityToBeAbsorbed].first].second = m_indexOfActiveComunity[comunityToBeAbsorbed].second;
	m_indexOfActiveComunity[m_indexOfActiveComunity[comunityToBeAbsorbed].second].first = m_indexOfActiveComunity[comunityToBeAbsorbed].first;

	m_firstActiveComunity = m_firstActiveComunity == comunityToBeAbsorbed ? m_hTotal.max().getPos().first : m_firstActiveComunity;
}

void Comunitat::fixMaxHeapAfterFusion(int communitiyToKeepAsFusionOfBoth,int communityToBeAbsorbed){
//	cout<<"communitiyToKeepAsFusionOfBoth: "<<communitiyToKeepAsFusionOfBoth<<endl;
//	cout<<"communityToBeAbsorbed: "<<communityToBeAbsorbed<<endl;
//	for (int i = 0;i < m_candidatesElementsToModificateInMaxHeap.size();i++){
//		cout<<m_candidatesElementsToModificateInMaxHeap[i]<<endl;
//	}
//	cout<<endl<<endl<<endl;
	for (int i = 0; i < m_candidatesElementsToModificateInMaxHeap.size();i++){
		int rowToModificate = m_candidatesElementsToModificateInMaxHeap[i];
		double newMaxDeltaQ = m_maxDeltaQOfRows[rowToModificate].second;

		pair<int,int> position = make_pair(rowToModificate,m_maxDeltaQOfRows[rowToModificate].first);
		ElemHeap elementToFix = ElemHeap(newMaxDeltaQ,position);
		if (rowToModificate != communitiyToKeepAsFusionOfBoth && rowToModificate != communityToBeAbsorbed){
			m_hTotal.modifElem(elementToFix);
		}
	}
	/*
	 * This is done to guarantee that the last element modified will be communityToKeepAsfusion.
	 * that community may be a neighbourd of a absorbed community
	 */

	pair<int,int> position = make_pair(communitiyToKeepAsFusionOfBoth,m_maxDeltaQOfRows[communitiyToKeepAsFusionOfBoth].first);
	double newMaxDeltaQ = m_maxDeltaQOfRows[communitiyToKeepAsFusionOfBoth].second;
	ElemHeap elementToFix = ElemHeap(newMaxDeltaQ,position);
	m_hTotal.modifElem(elementToFix);

	m_candidatesElementsToModificateInMaxHeap.clear();  // To use the same vector for each fusion
}

void Comunitat::fusiona(int comunityToBeAbsorbed, int comunityToKeepAsFusionOfBoth){
	vector<int> neighboursOfTheComunityToBeAbsorbed = getNeighbourds(comunityToBeAbsorbed);
	vector<int> neighboursOfTheComunityWhoAbsorbs = getNeighbourds(comunityToKeepAsFusionOfBoth);
	vector<int> comunityToKeep = { comunityToKeepAsFusionOfBoth };

	vector<int> commonNeighbourds = commonNeighbourdsOfFusion(comunityToBeAbsorbed,comunityToKeepAsFusionOfBoth,
			neighboursOfTheComunityToBeAbsorbed,
			neighboursOfTheComunityWhoAbsorbs);

	recalculateDeltaQOfNeighbourdsOfCommunityToBeAbsorbed(comunityToBeAbsorbed,comunityToKeepAsFusionOfBoth, neighboursOfTheComunityToBeAbsorbed);
	recalculateDeltaQOfNeighbourdsOfCommunityWhoAbsorbs(comunityToBeAbsorbed, comunityToKeepAsFusionOfBoth, neighboursOfTheComunityWhoAbsorbs);

	m_deltaQ[comunityToBeAbsorbed].clear();
	m_deltaQ[comunityToKeepAsFusionOfBoth].erase(make_pair(comunityToKeepAsFusionOfBoth, comunityToBeAbsorbed));

	recalculateMaxDeltaQOfNeighbourds(commonNeighbourds);
	recalculateMaxDeltaQOfNeighbourds(neighboursOfTheComunityToBeAbsorbed);
	recalculateMaxDeltaQOfNeighbourds(neighboursOfTheComunityWhoAbsorbs);
	recalculateMaxDeltaQOfNeighbourds(comunityToKeep);
	m_maxDeltaQOfRows[comunityToBeAbsorbed].second = -2; // out of range of Q

	neighboursOfTheComunityToBeAbsorbed.clear();
	neighboursOfTheComunityWhoAbsorbs.clear();
	commonNeighbourds.clear();
	comunityToKeep.clear();
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

vector<int> Comunitat::commonNeighbourdsOfFusion(int comunityToBeAbsorbed, int comunityToKeepAsFusionOfBoth,vector<int> &neighboursOfTheComunityToBeAbsorbed,vector<int> &neighboursOfTheComunityWhoAbsorbs){
	sort(neighboursOfTheComunityToBeAbsorbed.begin(),neighboursOfTheComunityToBeAbsorbed.end());
	sort(neighboursOfTheComunityWhoAbsorbs.begin(),neighboursOfTheComunityWhoAbsorbs.end());

	vector<int> commonNeighbours(neighboursOfTheComunityToBeAbsorbed.size() + neighboursOfTheComunityWhoAbsorbs.size(),-1);
	vector<int>::iterator lastElement,iter;

	lastElement = set_intersection(neighboursOfTheComunityToBeAbsorbed.begin(),neighboursOfTheComunityToBeAbsorbed.end(),
			neighboursOfTheComunityWhoAbsorbs.begin(),neighboursOfTheComunityWhoAbsorbs.end(),
			commonNeighbours.begin());

	vector<int> neighbourdsOfComunityToBeAborbedWithNoCommon;
	vector<int> neighbourdsOfComunityWhoAbsordsWithNoCommon;
	for (int j = 0; j < neighboursOfTheComunityToBeAbsorbed.size();j++){
		if (not existsElement(commonNeighbours, neighboursOfTheComunityToBeAbsorbed[j])){
			neighbourdsOfComunityToBeAborbedWithNoCommon.push_back(neighboursOfTheComunityToBeAbsorbed[j]);
		}
	}

	for (int j = 0; j < neighboursOfTheComunityWhoAbsorbs.size();j++){
		if (not existsElement(commonNeighbours,neighboursOfTheComunityWhoAbsorbs[j])){
			neighbourdsOfComunityWhoAbsordsWithNoCommon.push_back(neighboursOfTheComunityWhoAbsorbs[j]);
		}
	}

	neighboursOfTheComunityToBeAbsorbed.clear();
	neighboursOfTheComunityToBeAbsorbed = neighbourdsOfComunityToBeAborbedWithNoCommon;
	neighboursOfTheComunityWhoAbsorbs.clear();
	neighboursOfTheComunityWhoAbsorbs = neighbourdsOfComunityWhoAbsordsWithNoCommon;

	map<pair<int,int>,double> mapOfComunityToKeepAsFusion = m_deltaQ[comunityToKeepAsFusionOfBoth];
	map<pair<int,int>,double> mapOfComunityToBeAbsorbed = m_deltaQ[comunityToBeAbsorbed];

	for (iter = commonNeighbours.begin(); iter != lastElement; ++iter){
		map<pair<int,int>,double> mapOfNeighbourds = m_deltaQ[*iter];

		pair<int,int> keyToSearch1 = make_pair(*iter, comunityToBeAbsorbed);
		pair<int,int> keyToSearch2 = make_pair(*iter,comunityToKeepAsFusionOfBoth);
		pair<int,int> keyToSearch3 = make_pair(comunityToKeepAsFusionOfBoth,*iter);
		pair<int,int> keyToSearch4 = make_pair(comunityToBeAbsorbed,*iter);

		mapOfNeighbourds[keyToSearch2] = mapOfNeighbourds[keyToSearch2] + mapOfNeighbourds[keyToSearch1];
		mapOfNeighbourds.erase(keyToSearch1);
		mapOfComunityToKeepAsFusion[keyToSearch3] = mapOfComunityToKeepAsFusion[keyToSearch3] + mapOfComunityToBeAbsorbed[keyToSearch4];
		m_deltaQ[*iter] = mapOfNeighbourds;
	}
	m_deltaQ[comunityToKeepAsFusionOfBoth] = mapOfComunityToKeepAsFusion;
	return commonNeighbours;
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

void Comunitat::recalculateMaxDeltaQOfNeighbourds(vector<int> const neighbourds){
	for (int i = 0; i < neighbourds.size();i++){
		if (neighbourds[i] == -1){  // This case is for commonNeighbourds
			break;
		}

		int actualNeigbourd = neighbourds[i];
		map<pair<int,int>,double> aux = m_deltaQ[actualNeigbourd];
		map<pair<int,int>,double>::iterator mapIterator;
		double maxDeltaQInRow = 0;
		pair<int,int> keyofMaxDeltaQ;

		for(mapIterator = aux.begin();mapIterator != aux.end();++mapIterator){
			if (mapIterator->second > maxDeltaQInRow){
				maxDeltaQInRow = mapIterator->second;
				keyofMaxDeltaQ = make_pair(mapIterator->first.first, mapIterator->first.second);
			}
		}

		pair<int,double> rowOfMaxDeltaQAndValue = make_pair(keyofMaxDeltaQ.second, maxDeltaQInRow);
		m_maxDeltaQOfRows[actualNeigbourd] = rowOfMaxDeltaQAndValue;

		if ( not existsElement(m_candidatesElementsToModificateInMaxHeap,actualNeigbourd)){
			m_candidatesElementsToModificateInMaxHeap.push_back(actualNeigbourd);
		}
	}
}

bool Comunitat::existsElement(vector<int> const neighbourds,int elementToCheck){
	for (int i = 0; i < neighbourds.size();i++){
		if (elementToCheck == neighbourds[i] )
			return true;
	}
	return false;
}
