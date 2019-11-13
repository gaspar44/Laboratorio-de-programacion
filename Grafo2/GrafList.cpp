#include "GrafList.h"
#include <iomanip>
#include <algorithm>

struct ComparaPair
{
	ComparaPair(int val) : m_valor(val) {}
	bool operator()(const std::pair<int, int>& elem) const 
	{
		return m_valor == elem.first;
	}
	bool operator==(const std::pair<int, int>& elem) const
	{
		return m_valor == elem.first;
	}
private:
	int m_valor;
};

Graf::Graf(bool dirigit)
{
	m_numNodes = 0;
	m_numArestes = 0;
	m_dirigit = dirigit;
}

Graf::Graf(vector<string>& nodes, vector<vector<int>>& parNodes, bool dirigit)
{
	m_numNodes = nodes.size();
	m_nodes.resize(m_numNodes);
	m_veins.resize(m_numNodes);
	m_dirigit = dirigit;
	m_numArestes = parNodes.size();

	for (int i = 0; i < m_numNodes; i++)
	{
		m_nodes[i] = nodes[i];		
	}
	for (int j = 0; j < parNodes.size(); j++)
	{
		if ((parNodes[j][0] < m_numNodes) && (parNodes[j][1] < m_numNodes) && 
			(parNodes[j][0] >= 0) && (parNodes[j][1]>= 0))
		{
			m_veins[parNodes[j][0]].emplace_back(pair<int,int>(parNodes[j][1],1));
			if (!dirigit)
			{
				m_veins[parNodes[j][1]].emplace_back(pair<int, int>(parNodes[j][0], 1));
			}
		}			
	}
}
Graf::Graf(vector<string>& nodes, vector<vector<int>>& parNodes, vector<int>& pesos,bool dirigit)
{
	m_numNodes = nodes.size();
	m_nodes.resize(m_numNodes);
	m_veins.resize(m_numNodes);
	m_dirigit = dirigit;
	m_numArestes = parNodes.size();

	for (int i = 0; i < m_numNodes; i++)
	{
		m_nodes[i] = nodes[i];
	}
	for (int j = 0; j < parNodes.size(); j++)
	{
		if ((parNodes[j][0] < m_numNodes) && (parNodes[j][1] < m_numNodes) &&
			(parNodes[j][0] >= 0) && (parNodes[j][1] >= 0))
		{
			m_veins[parNodes[j][0]].emplace_back(pair<int, int>(parNodes[j][1], pesos[j]));
			if (!dirigit)
			{
				m_veins[parNodes[j][1]].emplace_back(pair<int, int>(parNodes[j][0], pesos[j]));
			}
		}
	}
}
Graf::~Graf()
{
}

void Graf::inserirAresta(int posNode1, int posNode2)
{
	if ((posNode1 < m_numNodes) && (posNode2 < m_numNodes) && (posNode1 >= 0) && (posNode2 >= 0))
	{
		m_veins[posNode1].emplace_back(pair<int,int>(posNode2,1));
		if (!m_dirigit)
		{
			m_veins[posNode2].emplace_back(pair<int, int>(posNode1, 1));
		}
		m_numArestes++;
	}	
}

void Graf::inserirAresta(int posNode1, int posNode2, int pes)
{
	if ((posNode1 < m_numNodes) && (posNode2 < m_numNodes)&& (posNode1 >=0) && (posNode2 >= 0))
	{
		m_veins[posNode1].emplace_back(pair<int, int>(posNode2, pes));
		if (!m_dirigit)
		{
			m_veins[posNode2].emplace_back(pair<int, int>(posNode1, pes));
		}
		m_numArestes++;
	}
}


void Graf::eliminarAresta(int posNode1, int posNode2)
{
	list<pair<int, int>>::iterator itAre = find_if(m_veins[posNode1].begin(), m_veins[posNode1].end(),ComparaPair(posNode2));
	if (itAre != m_veins[posNode1].end())
	{
		m_veins[posNode1].erase(itAre);
		m_numArestes--;
	}
	if (!m_dirigit)
	{
		itAre = find_if(m_veins[posNode2].begin(), m_veins[posNode2].end(), ComparaPair(posNode1));
		if (itAre != m_veins[posNode2].end())
		{
			m_veins[posNode2].erase(itAre);
		}		
	}
}

void Graf::afegirNode(string node)
{
	m_nodes.push_back(node);
	m_numNodes++;	
	m_veins.resize(m_numNodes);
}


void Graf::eliminarNode(string node)
{
	//busquem la posici� del node a esborrar
	vector<string>::iterator it;

	it = find(m_nodes.begin(), m_nodes.end(), node);
	//mirem si node existeix
	if (it != m_nodes.end())
	{
		//Obtenim index del node
		int nodeIndex = it - m_nodes.begin();
		
		// eliminem el node del vector de nodes
		m_nodes.erase(it);
		//Eliminem arestes desde el node
		m_veins.erase(m_veins.begin()+ nodeIndex);
		//Eliminem arestes cap al node
	
		for (int i = 0; i < m_veins.size(); i++)
		{//eliminem cada aresta sense ponderar
			m_veins[i].remove_if(ComparaPair(nodeIndex));
		}
		m_numNodes--;
	}	
}

vector<vector<string>> Graf::cicles(){
	vector<vector<string>> ret;
	vector<string>::iterator it;

	for (it = m_nodes.begin(); it != m_nodes.end(); ++it) {
		vector<int> elementsToInsert;
		int integerNode = taskToNode(*it);
		elementsToInsert.push_back(integerNode);

		if (!m_dirigit){
			dirigitCicleCalculator(elementsToInsert,0);
		}
		
		else {
			noDirigitCicleCalculator(elementsToInsert,0);
		}

		sort(elementsToInsert.begin(), elementsToInsert.end());
		insertToRet(elementsToInsert, ret);
	}
	return ret;
}

void Graf::insertToRet(vector<int> elementsToInsert,vector<vector<string>> &ret){
	vector<string> cicle;
	vector<int>::iterator it;

	if (elementsToInsert.size() == 0)
		return;

	for(it = elementsToInsert.begin();it != elementsToInsert.end();++it){
		string name = to_string(*it + 1);
		string nodeName = "Tasca " + name;

		cicle.push_back(nodeName);
	}

	if (find(ret.begin(),ret.end(),cicle) == ret.end() ){
		ret.push_back(cicle);
	}
}

int Graf::taskToNode(string nodeToParse){
	string subString = nodeToParse.substr(nodeToParse.size() - 2, nodeToParse.size() -1);
	int node = stoi(subString);
	return node - 1;
}

void Graf::dirigitCicleCalculator(vector<int> &traveledPath,int maxNumberCicle){
	int foundElements;
	while (maxNumberCicle != m_maxCicleCalculator){
		list<pair<int,int>> visibleNodes = m_veins[traveledPath[traveledPath.size() - 1]];
		list<pair<int,int>>::iterator it;
		for (it = visibleNodes.begin(); it != visibleNodes.end();++it){
			list<pair<int,int>> visibleNodesFromVisitedNode = m_veins[it->first];
			if(subConjunt(traveledPath,visibleNodesFromVisitedNode,foundElements)) { // it's inside
				traveledPath.push_back(it->first);
			}
		}
		maxNumberCicle++;
	}

	if (traveledPath.size() != m_maxCicleCalculator){
		traveledPath.clear();
	}
}

void Graf::noDirigitCicleCalculator(vector<int> &traveledPath,int numberOfNodesToVisit){
		int foundElements;
		while (numberOfNodesToVisit != m_maxCicleCalculator){
		list<pair<int,int>> visibleNodes = m_veins[traveledPath[traveledPath.size() - 1]];
		list<pair<int,int>>::iterator firstLevelIterator;
		list<pair<int,int>>::iterator secondLevelIterator;
		for (firstLevelIterator = visibleNodes.begin(); firstLevelIterator != visibleNodes.end();++firstLevelIterator){
			list<pair<int,int>> visibleNodesFromVisitedNode = m_veins[firstLevelIterator->first];

			for (secondLevelIterator = visibleNodesFromVisitedNode.begin(); secondLevelIterator != visibleNodesFromVisitedNode.end(); ++secondLevelIterator){
				list<pair<int,int>> visibleNodesFromNode = m_veins[secondLevelIterator->first];
				
				if(subConjunt(traveledPath,visibleNodesFromNode,foundElements)) { // it's inside
					traveledPath.push_back(firstLevelIterator->first);
					traveledPath.push_back(secondLevelIterator->first);
					return;
				}
			}
		}
		numberOfNodesToVisit++;
	}

	if (traveledPath.size() != m_maxCicleCalculator){
		traveledPath.clear();
	}
}

bool Graf::subConjunt(vector<int> &traveledPath,list<pair<int,int>> aristas,int &foundElements){
	vector<int>::iterator travelerIterator;
	list<pair<int,int>>::iterator aristasIterator;
	foundElements = 0;

	for(travelerIterator = traveledPath.begin(); travelerIterator != traveledPath.end();++travelerIterator){
		for(aristasIterator = aristas.begin(); aristasIterator != aristas.end();++aristasIterator){
			if(*travelerIterator == aristasIterator->first){
				foundElements = foundElements + 1;
			}
		}
	}
	return foundElements == traveledPath.size();
}

int Graf::grauOutNode(string node)
{
	int nodeToSearch = taskToNode(node);
	return m_veins[nodeToSearch].size();
}

int Graf::grauInNode(string node)
{
	int nodeToSearch = taskToNode(node);
	if (!m_dirigit)
		return m_veins[nodeToSearch].size();
	return 5;
	
}


void Graf::camins(string node1, string node2, vector<list<string>>& camins)
{

}


void Graf::mostra()
{
	// imprimim el nom dels v�rtexs
	cout << "Graf: NUMNODES: " << m_numNodes << " ; NUMARESTES: " << m_numArestes << ":" << endl;
	cout << "=====NODES=====" << endl;
	for (int i = 0; i < m_numNodes; i++)
	{
		int espai = 20;
		if (i == 0) espai--;
		for (int dig = i; dig > 0; dig /= 10)
		{
			espai -= 1;
		}
		cout << i << ":" << setw(espai) << m_nodes[i] << " ";
		for (list<pair<int,int>>::iterator it = m_veins[i].begin(); it != m_veins[i].end(); it++)
		{
			cout << "-----> ( " << m_nodes[(*it).first] <<"," << (*it).second << " )  ";			
		}
		cout << endl;
	}	
}

