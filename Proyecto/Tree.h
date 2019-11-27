/*
 * Tree.h
 *
 *  Created on: 25 nov. 2019
 *      Author: gaspar
 */

#ifndef TREE_H_
#define TREE_H_
#include <string>
using namespace std;

template <class T>
class Tree {
public:
	Tree() : m_data(nullptr), m_father(nullptr), m_left(nullptr), m_right(nullptr) {}
	Tree(const T& data) {
		m_left = nullptr;
		m_right = nullptr;
		m_father = nullptr;
		m_data = new T;
		*m_data = data;
	};

	Tree(const Tree<T>& t) {
		m_left = t.m_left;
		m_right = t.m_right;
		m_father = t.m_father;
		m_data = t.m_data;
	}

	Tree(string nomFitxer);
	~Tree();

	bool isLeave() const { return ((m_left == NULL) && (m_right == NULL)); }
	bool isEmpty() const { return (m_data == NULL);}
	Tree<T>* getRight(){ return m_right;}
	Tree<T>* getLeft() { return m_left; }
	void setRight(Tree<T>* tR);
	void setLeft(Tree<T>* tL);
	T& getData() { return (*m_data); }
	//template<T> friend std::ostream& operator<<(std::ostream& out, const Tree<T>& t);

private:
	Tree<T>* m_left;
	Tree<T>* m_right;
	Tree<T>* m_father;
	T* m_data;
	void TreeRec(ifstream& fitxerNodes, int h, Tree<T>* father);
	std::ostream& coutArbreRec(int n, std::ostream& out) const;
};


#endif /* TREE_H_ */
