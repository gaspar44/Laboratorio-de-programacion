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
#include "Heap.h"
#include "Tree.hpp"

class Comunitat {
public:
	Comunitat(MatriuSparse* pMAdj);
	Comunitat(const Comunitat& community);
	Comunitat& operator=(const Comunitat& community);
	~Comunitat() {
		if (m_deltaQ.size() != 0){
			m_deltaQ.clear();
		}

		if (m_indexOfActiveComunity.size() != 0){
			m_indexOfActiveComunity.clear();
		}
		if (m_maxDeltaQOfRows.size() != 0){
			m_maxDeltaQOfRows.clear();
		}

		if (m_k.size() != 0){
			m_k.clear();
		}

		if (m_A.size() != 0){
			m_A.clear();
		}

		if (m_vDendrograms.size() != 0){
			m_vDendrograms.clear();
		}

		if (m_candidatesElementsToModificateInMaxHeap.size() != 0){
			m_candidatesElementsToModificateInMaxHeap.clear();
		}
	};

	void calculaM2() { m_M2 = m_sparseMatrix->getNValues(); };
	void calculaK() { m_sparseMatrix->calculaGrau(m_k); };
	void calculaA();
	void creaDeltaQHeap();
	void creaIndexComs();
	void InicialitzaDendrograms() { m_sparseMatrix->calculaDendograms(m_vDendrograms); };
	void calculaComunitats(list<Tree<double>*>& listDendrogram);
	void fusiona(int comunityToBeAbsorbed, int comunityToKeepAsFusionOfBoth);
	void modificaVei(int com1, int com2, int vei, int cas);
	int getM2() { return m_M2; }
	void printTree() { cout<<m_hTotal<<endl; };

	vector<int> getK() { return m_k; }
	vector<double> getA() { return m_A; }
	vector<map<pair<int, int>, double>> getdeltaQ() { return m_deltaQ;}
	Heap gethTotal() { return m_hTotal;}
	vector<pair<int, int>> getIndexComs() { return m_indexOfActiveComunity; }
	void clear();

private:
	MatriuSparse* m_sparseMatrix;
	Heap m_hTotal;
	double m_Q;
	int m_M2;
	int m_firstActiveComunity;

	vector<map<pair<int, int>, double>> m_deltaQ;
	vector<pair<int, int>> m_indexOfActiveComunity;
	vector<pair<int, double>> m_maxDeltaQOfRows;
	vector<int> m_k;
	vector<double> m_A;
	vector<Tree<double>*> m_vDendrograms;
	vector<int> m_candidatesElementsToModificateInMaxHeap;

	vector<int> getNeighbourds(int comuintyToGetNeighbourd);
	vector<int> commonNeighbourdsOfFusion(int comunityToBeAbsorbed, int comunityToKeepAsFusionOfBoth,vector<int> &neighboursOfTheComunityToBeAbsorbed,vector<int> &neighboursOfTheComunityWhoAbsorbs);
	void recalculateDeltaQOfNeighbourdsOfCommunityToBeAbsorbed(int comunityToBeAbsorbed,int comunityToKeepAsFusionOfBoth, vector<int> &neighboursOfTheComunityToBeAbsorbed);
	void recalculateDeltaQOfNeighbourdsOfCommunityWhoAbsorbs(int comunityToBeAbsorbed,int comunityToKeepAsFusionOfBoth, vector<int> &neighboursOfTheComunityWhoAbsorbs);
	void getMaxDeltaQ(map<pair<int,int>,double> &aux, double &maxDeltaQInRow,pair<int,int> &keyOfMaxDeltaQ);
	void deleteAbsorbedComunityFromActiveCommunities(int comunityToBeAbsorbed);
	void recalculateMaxDeltaQOfNeighbourds(vector<int> const neighbourds);
	void fixMaxHeapAfterFusion(int communitiyToKeepAsFusionOfBoth,int communityToBeAbsorbed);
	bool existsElement(vector<int> const neighbourds,int elementToCheck);
	void updateDendogram(int communitiyToKeepAsFusionOfBoth,int communityToBeAbsorbed,double actualDeltaQ);
};

#endif /* COMUNITATS_H_ */
