#include "graf.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <queue>

#include <bits/stdc++.h>

using namespace std;


Graf::Graf()
{
	m_numNodes = 0;
	m_numArestes = 0;
	m_dirigit = false;
}

Graf::Graf(vector<string>& nodes, vector<vector<int>> parellesNodes, bool dirigit)
{
	m_nodes = nodes; 
	m_numNodes = m_nodes.size();
	m_dirigit = dirigit;
	crearMatriu(parellesNodes);
}

Graf::Graf(vector<string>& nodes, vector<vector<int>> parellesNodes, vector<int> pesos, bool dirigit)
{
	m_nodes = nodes;
	m_numNodes = m_nodes.size();
	m_dirigit = dirigit;
	crearMatriu(parellesNodes, pesos);
}


Graf::~Graf()
{
}

void Graf::crearMatriu(vector<vector<int>> parelles)
{
	m_matriuAdj.resize(m_numNodes);
	for (int i=0; i<m_numNodes;i++)
	{
		m_matriuAdj[i].resize(m_numNodes,0);
	}

	for (int i = 0; i < parelles.size(); i++)
	{
		m_matriuAdj[parelles[i][0]][parelles[i][1]] = 1;
		if (!m_dirigit)
			m_matriuAdj[parelles[i][1]][parelles[i][0]] = 1;
	}
}

void Graf::crearMatriu(vector<vector<int>> parelles, vector<int> pesos)
{
	m_matriuAdj.resize(m_numNodes);
	for (auto &it : m_matriuAdj)
	{
		it.resize(m_numNodes);
	}

	for (int i = 0; i < parelles.size(); i++)
	{
		m_matriuAdj[parelles[i][0]][parelles[i][1]] = pesos[i];
		if (!m_dirigit)
			m_matriuAdj[parelles[i][1]][parelles[i][0]] = pesos[i];
	}
}

void Graf::inserirAresta(int posNode1, int posNode2)
{
	m_matriuAdj[posNode1][posNode2] = 1;
	if (!m_dirigit)
		m_matriuAdj[posNode2][posNode1] = 1;
}

void Graf::inserirAresta(int posNode1, int posNode2, int pes)
{
	m_matriuAdj[posNode1][posNode2] = pes;
	if (!m_dirigit)
		m_matriuAdj[posNode2][posNode1] = pes;
}


void Graf::eliminarAresta(int posNode1, int posNode2)
{
	m_matriuAdj[posNode1][posNode2] = 0;
	if (!m_dirigit)
		m_matriuAdj[posNode2][posNode1] = 0;
}

void Graf::afegirNode(string node)
{
	//m_nodes.resize(m_numNodes);
	m_nodes.push_back(node);

	// add a row
	m_matriuAdj.push_back(std::vector<int>(m_numNodes));

	m_numNodes++;

	//m_matriuAdj.resize(m_numNodes);
	for (int i = 0; i < m_numNodes; i++) m_matriuAdj[i].push_back(0);
}

void Graf::eliminarNode(string node)
{
	//busquem la posici� del node a esborrar
	vector<string>::iterator it;
	
	it = find(m_nodes.begin(), m_nodes.end(), node);

	//eliminem el node del vector de nodes i de la matriu d'adjacencia
	if (it != m_nodes.end())
	{
		int pos = distance(m_nodes.begin(), it);
		// eliminem el node del vector de nodes
		//m_nodes.erase(m_nodes.begin() + pos);
		m_nodes.erase(it);

		// eliminem la fila i la columna de la matriu d'adjacencia corresponents a aquest node
		m_matriuAdj.erase(m_matriuAdj.begin() + pos);

		for (int i = 0; i < m_numNodes; i++)
		{			
			m_matriuAdj[i].erase(m_matriuAdj[i].begin() + pos);
		}
		m_numNodes--;
	}
}

void Graf::mostra() 
{
	int mida_c = 4;
	// imprimim el nom dels v�rtexs
	cout << setw(mida_c) << " ";
	for (int j = 0; j < m_numNodes; j++)
	{

		cout << setw(mida_c) << m_nodes[j] << " ";
	}
	cout << endl;

	for (int i = 0; i < m_numNodes; i++)
	{
		cout << setw(10) << m_nodes[i] << " ";
		for (int j = 0; j < m_numNodes; j++)
		{			
			cout << setw(mida_c) << m_matriuAdj[i][j] << " ";
		}
		cout << endl;
	}	
}


void Graf::BFS(string nodeInicial, queue<string>& recorregut)
{
	vector<string>::iterator itNode = find(m_nodes.begin(), m_nodes.end(), nodeInicial);
	vector<bool> visitat;
	visitat.resize(m_numNodes, false);
	queue<int> pendents;

	if (itNode != m_nodes.end())
	{
		int pos = distance(m_nodes.begin(), itNode);
		visitat[pos] = true;
		pendents.push(pos);

		while (!pendents.empty())
		{
			int nodeActual = pendents.front();
			pendents.pop();
			recorregut.push(m_nodes[nodeActual]);

			// posem a la cua tots els nodes adjacents a nodeActual no visitats
			for (int col=0; col<m_numNodes; col++)
			{
				if((m_matriuAdj[nodeActual][col]!=0)&& (!visitat[col]))
				{
					pendents.push(col);
					visitat[col] = true;
				}
			}
		}
	}
}

void Graf::BFS(string nodeInicial, string nodeFinal, queue<string>& recorregut, stack<string>& cami)
{
	vector<string>::iterator iterator1, iterator2;
	vector<bool> visited(m_numNodes, false);
	list<int> posiblePaths;
	vector<list<int>> allPaths;

	iterator1 = find(m_nodes.begin(), m_nodes.end(), nodeInicial);
	iterator2 = find(m_nodes.begin(), m_nodes.end(), nodeFinal);
	if ((iterator1 != m_nodes.end()) && (iterator2 != m_nodes.end())) {//Si els nodes existeixen
		int positionOfFirstNode = distance(m_nodes.begin(), iterator1);
		int positionOfFinalNode = distance(m_nodes.begin(), iterator2);
		getPosiblePaths(positionOfFirstNode, positionOfFinalNode, visited, posiblePaths,allPaths);
	}

	list<int> minPath = getMinimunPath(allPaths);
	setTravelToStack(minPath,cami);
}

void Graf::setTravelToStack(list<int> minPath, stack<string> & path){
	list<int>::iterator iter;
	vector<string> helper;


	for (iter = minPath.begin(); iter != minPath.end();++iter){
		cout<<m_nodes[*iter]<<endl;
		helper.push_back(m_nodes[*iter]);
	}

	if (helper.size() != 0){
		for (int i = helper.size() - 1; i != 0;i--){
			path.push(helper[i]);
		}
		path.push(helper[0]);
	}

}

list<int> Graf::getMinimunPath(vector<list<int>> allPaths){
	list<int> minPath;
	int min = 9999;

	for (int i = 0;i < allPaths.size();i++){
		if (allPaths[i].size() < min){
			min = allPaths[i].size();
			minPath = allPaths[i];
		}
	}

	return minPath;
}

void Graf::BFS(string nodeInicial, int distancia, queue<string>& recorregut)
{
}

int Graf::BFS(string nodeInicial, string nodeFinal, queue<string>& recorregut){
	vector<string>::iterator iterator1, iterator2;
	vector<bool> visited(m_numNodes, false);
	list<int> posiblePaths;
	vector<list<int>> allPaths;

	iterator1 = find(m_nodes.begin(), m_nodes.end(), nodeInicial);
	iterator2 = find(m_nodes.begin(), m_nodes.end(), nodeFinal);
	if ((iterator1 != m_nodes.end()) && (iterator2 != m_nodes.end())) {//Si els nodes existeixen
		int positionOfFirstNode = distance(m_nodes.begin(), iterator1);
		int positionOfFinalNode = distance(m_nodes.begin(), iterator2);
		getPosiblePaths(positionOfFirstNode, positionOfFinalNode, visited, posiblePaths,allPaths);
	}

	if (allPaths.size() == 0)
		return -1;

	return getMinimunPathSize(allPaths);
}

int Graf::getMinimunPathSize(vector<list<int>> allPaths){
	vector<list<int>>::iterator iter;
	vector<int> sizes;
	for(iter = allPaths.begin(); iter != allPaths.end();++iter){
		sizes.push_back(iter->size());
	}

	return *min_element(sizes.begin(), sizes.end()) -1;

}

void Graf::getPosiblePaths(int initialNode, int endNode, vector<bool> visited,list<int> paths,vector<list<int>> &allPaths){
	visited[initialNode] = true;
	paths.push_back(initialNode);

	if (initialNode == endNode) {
		allPaths.push_back(paths);
	}

	else 	{
		for (int i = 0; i < m_numNodes; i++){
			if (m_matriuAdj[initialNode][i] != 0){
				if (!visited[i]){
					getPosiblePaths(i, endNode, visited, paths,allPaths);
				}
			}
		}
	}
	// Esborrem vertex actual del path I el marquem com a no visitat
	paths.pop_back();
	visited[initialNode] = false;
}
