#pragma once
#include <algorithm>  
#include <list>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

class Graf
{
public:
	Graf(bool dirigit);
	Graf(vector<string>& nodes, vector<vector<int>>& parellesNodes, bool dirigit);
	Graf(vector<string>& nodes, vector<vector<int>>& parellesNodes, vector<int>& pesos, bool dirigit);
	~Graf();
	int getNumNodes() { return m_numNodes; }

	void inserirAresta(int posNode1, int posNode2);
	void inserirAresta(int posNode1, int posNode2, int pes);
	void eliminarAresta(int posNode1, int posNode2);

	void afegirNode(string node);
	void eliminarNode(string node);

	vector<vector<string>> cicles();
	int grauOutNode(string node);
	int grauInNode(string node);
	void camins(string node1, string node2, vector<list<string>>& camins);
	
	void mostra();

private:
	//Aqui a string podem posar TNode per tenir nodes de qualsevol tipus
	vector<list<pair<int,int>>> m_veins;
	vector<string> m_nodes;
	int m_numNodes;
	int m_numArestes;
	bool m_dirigit;
	void cicleCalculator(vector<int> &traveledPath,int maxNumberCicle);
};
