/*
 * MatriuDispersa.h
 *
 *  Created on: 14 oct. 2019
 *      Author: gaspar
 */

#ifndef SPARSEMATRIX_H_
#define SPARSEMATRIX_H_
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class SparseMatrix {
public:
	SparseMatrix() : m_rows(0), m_columns(0), m_noZeroElements(0) {};
	~SparseMatrix() {};
	SparseMatrix(string fileName);
	SparseMatrix(int rows, int columns) : m_rows(rows), m_columns(columns), m_noZeroElements(0) {};
	SparseMatrix(const SparseMatrix& m);
	void init(int rows,int columns) : m_rows(rows), m_columns(columns), m_noZeroElements(0) {};
	int getNFiles() { return m_rows; };
	int getNColumnes() { return m_columns; } ;
	void setValor(int row,int column,double value);
	bool getValor(int row,int column,double &value);
	vector<float> operator *(const vector<float> &vec);
	SparseMatrix operator *(const double n);
	SparseMatrix operator/(const double n);
	SparseMatrix& operator= (const SparseMatrix &m);
	friend ostream& operator<<(ostream &out, SparseMatrix& sp);

private:
	map<pair<int,int>,double> m_dictionary;
	int m_rows;
	int m_columns;
	int m_noZeroElements;

	int getMaxNumberOfNodes(string fileName);

};

template<typename T>
ostream& operator <<(ostream & os, vector<T> vec){
	for (int i = 0; i <vec.size();i++){
		os << "[POS: "<<i<<" ;"<<" VAL: "<<vec.at(i)<<" ]"<<endl;
	}
	return os;
}


#endif /* SPARSEMATRIX_H_ */
