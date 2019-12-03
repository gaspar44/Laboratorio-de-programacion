/*
 * MatriuDispersa.h
 *
 *  Created on: 14 oct. 2019
 *      Author: gaspar
 */

#ifndef MATRIUSPARSE_H_
#define MATRIUSPARSE_H_
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "Tree.h"

using namespace std;

class MatriuSparse {
public:
	MatriuSparse() : m_dimension(0), m_noZeroElements(0), m_aristas(0) {};
	~MatriuSparse() {};
	MatriuSparse(string fileName);
	MatriuSparse(int rows, int columns) : m_dimension(rows), m_noZeroElements(0), m_aristas(0) {};
	MatriuSparse(const MatriuSparse& m);
	void init(int rows,int columns) { m_dimension = rows; m_noZeroElements= 0 ;};
	int getNFiles() { return m_dimension; };
	int getNColumnes() { return m_dimension; } ;
	void setVal(int row,int column,float value);
	bool getVal(int row,int column,float &value);
	int getNValues() const { return m_gradesIn.size() * 2; };
	void calculaGrau(vector<int> &graus);
	void creapMaps(vector<map<pair<int,int>,double>> &vMaps);
	void calculaDendograms(vector<Tree<double>*> &vDendogramns);
	void clear();

	vector<float> operator *(const vector<float> &vec);
	MatriuSparse operator *(const float n);
	MatriuSparse operator/(const float n);
	MatriuSparse& operator= (const MatriuSparse &m);
	friend ostream& operator<<(ostream &out, MatriuSparse& sp);

private:
	map<pair<int,int>,float> m_dictionary;
	map<int,int> m_gradesIn;
	int m_dimension;
	int m_noZeroElements;
	int m_aristas;

	int getMaxNumberOfNodes(string fileName);

};

template<typename T>
ostream& operator <<(ostream & os, vector<T> vec){
	for (int i = 0; i <vec.size();i++){
		os << "[POS: "<<i<<" ;"<<" VAL: "<<vec.at(i)<<" ]"<<endl;
	}
	return os;
}

#endif /* MATRIUSPARSE_H_ */
