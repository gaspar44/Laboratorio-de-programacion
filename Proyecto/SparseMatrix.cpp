/*
 * MatriuDispersa.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: gaspar
 */

#include "SparseMatrix.h"

#include <iostream>
#include <fstream>
#include <iterator>

SparseMatrix::SparseMatrix(string fileName) {
	int rowToWrite;
	int columnToWrite;
	int rowsAndColumnsToReserve = getMaxNumberOfNodes(fileName) + 1;

	m_rows = rowsAndColumnsToReserve;
	m_columns = rowsAndColumnsToReserve;

	ifstream fileToCreateMatrix(fileName);
	string readedLine;

	while(!fileToCreateMatrix.eof()){
		fileToCreateMatrix>>rowToWrite>>columnToWrite;
		setValor(rowToWrite, columnToWrite, 1);
	}

	fileToCreateMatrix.close();
}

SparseMatrix::SparseMatrix(const SparseMatrix &m){
	m_noZeroElements = m.m_noZeroElements;
	m_rows = m.m_rows;
	m_columns = m.m_columns;
	m_dictionary = m.m_dictionary;
}

void SparseMatrix::setValor(int row,int column,double value){
	if (value == 0)
		return;

	pair<int,int> key = make_pair(row, column);

	if (m_dictionary[key] == 0) {
		if (row > m_rows){
			m_rows = row + 1;
		}

		if (column > m_columns){
			m_columns = column + 1 ;
		}

		m_dictionary[key] = value;
		m_noZeroElements = m_noZeroElements + 1;
	}
}

bool SparseMatrix::getValor(int row,int column,double &value){
	if (row > m_rows || column > m_columns){
		value = 0;
		return false;
	}

	pair<int,int> key = make_pair(row,column);
	value = m_dictionary[key];
	return true;
}

SparseMatrix SparseMatrix::operator *(const double n){
	SparseMatrix sp = *this;
	map<pair<int,int>,double>::iterator it;

	for (it = sp.m_dictionary.begin(); it != sp.m_dictionary.end();++it){
		(sp.m_dictionary)[it->first] = (sp.m_dictionary)[it->first] * n;
	}

	return sp;

}


ostream& operator<<(ostream &out, SparseMatrix& sp){
	map<pair<int,int>,double>::iterator it;
	out <<"MATRIU DE (FILES: "<<sp.m_rows<<" COLUMNES: "<<sp.m_columns<<" )"<<endl;
	out <<"VALORS (FILA::COL::VALOR)"<<endl;

	for (it = sp.m_dictionary.begin(); it != sp.m_dictionary.end();++it){
		out << "( " <<(it->first).first<<" :: "<<(it->first).second<<" :: "<<it->second<< " )"<<endl;
	}

	return out;

}

SparseMatrix& SparseMatrix::operator =(const SparseMatrix &m){
	m_noZeroElements = m.m_noZeroElements;
	m_rows = m.m_rows;
	m_columns = m.m_columns;
	m_dictionary = m.m_dictionary;
	return *this;
}


int SparseMatrix::getMaxNumberOfNodes(string fileName){
	ifstream fileToCheckNodes(fileName);
	int maxValue;
	int other;

	while ( !fileToCheckNodes.eof() ){
		fileToCheckNodes >> maxValue>>other;
	}

	return maxValue;
}
