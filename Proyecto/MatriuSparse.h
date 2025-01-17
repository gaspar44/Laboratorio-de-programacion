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

using namespace std;

class MatriuSparse {
public:
	MatriuSparse() : m_dimension(0), m_noZeroElements(0) {};
	~MatriuSparse() {};
	MatriuSparse(string fileName);
	MatriuSparse(int rows, int columns) : m_dimension(rows), m_noZeroElements(0) {};
	MatriuSparse(const MatriuSparse& m);
	void init(int rows,int columns) { m_dimension = rows; m_noZeroElements= 0 ;};
	int getNFiles() { return m_dimension; };
	int getNColumnes() { return m_dimension; } ;
	void setVal(int row,int column,float value);
	bool getVal(int row,int column,float &value);
	vector<float> operator *(const vector<float> &vec);
	MatriuSparse operator *(const float n);
	MatriuSparse operator/(const float n);
	MatriuSparse& operator= (const MatriuSparse &m);
	friend ostream& operator<<(ostream &out, MatriuSparse& sp);

private:
	map<pair<int,int>,float> m_dictionary;
	int m_dimension;
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


#endif /* MATRIUSPARSE_H_ */
