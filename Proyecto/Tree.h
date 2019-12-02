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
	void setRight(Tree<T>* tR) {
		m_right = tR;

		if (m_right != NULL){
			m_right->m_father = this;
		}
	}
	void setLeft(Tree<T>* tL) {
		m_left = tL;

		if (m_left != NULL){
			m_left->m_father = this;
		}
	};
	T& getData() { return (*m_data); }
	friend std::ostream& operator<<(std::ostream& out, const Tree<T>& t) {
		t.coutArbreRec(0, out);
		return out;
	}

private:
	Tree<T>* m_left;
	Tree<T>* m_right;
	Tree<T>* m_father;
	T* m_data;
	void TreeRec(ifstream& fitxerNodes, int h, Tree<T>* father);
	std::ostream& coutArbreRec(int n, std::ostream& out) const;
};

template<class T>
std::ostream& Tree<T>::coutArbreRec(int n, std::ostream& out) const
{
	if (isEmpty())
	{//Pintem arbre buit
		out << "Comment :=>> ";
		for (int i = 0; i < n; i++)
		{
			out << "|--";
		}
		out << "-->BUIT" << endl;
	}
	else
	{
		out << "Comment :=>> ";
		for (int i = 0; i < n; i++)
		{
			out << "|--";
		}
		out << "|-->";
		out << (*m_data) << endl;
		if (!isLeave())
		{
			if (m_left != NULL)
			{
				m_left->coutArbreRec(n + 1,out);
			}
			else
			{
				out << "Comment :=>> ";
				for (int i = 0; i < n + 1; i++)
				{
					out << "|--";
				}
				out << "|-->BUIT" << endl;
			}
			if (m_right != NULL)
			{
				m_right->coutArbreRec(n + 1,out);
			}
			else
			{
				out << "Comment :=>> ";
				for (int i = 0; i < n + 1; i++)
				{
					out << "|--";
				}
				out << "|-->BUIT" << endl;
			}
		}
	}
	return out;
}

#endif /* TREE_H_ */
