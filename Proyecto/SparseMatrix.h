/*
 * MatriuDispersa.h
 *
 *  Created on: 14 oct. 2019
 *      Author: gaspar
 */

#ifndef SPARSEMATRIX_H_
#define SPARSEMATRIX_H_
#include <string>
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
	void init(int rows,int columns);
	int getNFiles() { return m_rows; };
	int getNColumnes() { return m_columns; } ;
	bool getValor(int row,int column,double &value);
	void setValor(int row,int column,double value);
	SparseMatrix operator *(const double n);
	vector<float> operator *(const vector<float> &vec);
	SparseMatrix operator/(const double n);
	friend ostream& operator<<(ostream &out, SparseMatrix& sp);

private:
	map<pair<int,int>,double> m_values;
	int m_rows;
	int m_columns;
	int m_noZeroElements;

	int getMaxNumberOfNodes(string fileName);

};


#endif /* SPARSEMATRIX_H_ */
