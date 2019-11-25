/*
 * MatriuDispersa.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: gaspar
 */

#include <iostream>
#include <fstream>
#include <iterator>
#include "MatriuSparse.h"

MatriuSparse::MatriuSparse(string fileName) {
	int rowToWrite;
	int columnToWrite;
	m_dimension = getMaxNumberOfNodes(fileName);

	ifstream fileToCreateMatrix(fileName);
	string readedLine;

	while(!fileToCreateMatrix.eof()){
		fileToCreateMatrix>>rowToWrite>>columnToWrite;
		setVal(rowToWrite, columnToWrite, 1);
	}

	fileToCreateMatrix.close();
}

MatriuSparse::MatriuSparse(const MatriuSparse &m){
	m_noZeroElements = m.m_noZeroElements;
	m_dimension = m.m_dimension;
	m_dictionary = m.m_dictionary;
	m_aristas = m.m_aristas;
	m_gradesIn = m.m_gradesIn;
}

void MatriuSparse::creapMaps(vector<map<pair<int,int>,float>> &vMaps){
	map<pair<int,int>,float> aux;
	aux.clear();
	vMaps.resize(m_dimension,aux);
	map<pair<int,int>,float>::iterator mapIterator;

	for (mapIterator = m_dictionary.begin(); mapIterator != m_dictionary.end(); ++mapIterator){
		cout<< "Creando clave "<<mapIterator->first.first<<" "<< mapIterator->first.second<<endl;
		pair <int,int> key = make_pair(mapIterator->first.first, mapIterator->first.second);
		map<pair<int,int>,float> mapOfVector = vMaps[mapIterator->first.first];
		mapOfVector[key] = 0;
		vMaps[mapIterator->first.first] = mapOfVector;
	}
}

void MatriuSparse::setVal(int row,int column,float value){
	if (value == 0)
		return;

	pair<int,int> key1 = make_pair(row, column);
	pair<int,int> key2 = make_pair(column, row);

	if (row > m_dimension - 1 || column > m_dimension - 1){
		m_dimension = row > column ? row + 1 : column + 1;
	}
		m_dictionary[key1] = value;
		m_dictionary[key2] = value;
		m_gradesIn[row]+=1;
		m_aristas = m_aristas + 1;
		m_noZeroElements = m_noZeroElements + 1;
}


bool MatriuSparse::getVal(int row,int column,float &value){
	if (row >= m_dimension || column >= m_dimension){
		value = 0;
		return false;
	}

	pair<int,int> key = make_pair(row,column);

	value = m_dictionary[key];

	return true;
}


vector<float> MatriuSparse::operator *(const vector<float> &vec){
	if (vec.size() != m_dimension)
		throw "Error of vec for *";

	vector<float> resultVector;
	resultVector.resize(m_dimension);

	map<pair<int,int>,float>::iterator it;
	int actualRow = 0;
	float temp = 0;

	for (it = m_dictionary.begin(); it != m_dictionary.end(); ++it){

		if (actualRow != it->first.first) {
			resultVector.insert(resultVector.begin() + actualRow,temp);
			actualRow = it->first.first;
			temp = 0;
		}

		temp = temp + it->second * vec.at((it->first).second);
	}

	if (temp != 0){ // Necesario porque no le da a veces para insertar en la última iteración
		resultVector.insert(resultVector.begin() + actualRow,temp);
	}

	return resultVector;
}

MatriuSparse MatriuSparse::operator *(const float n){
	MatriuSparse sp = *this;
	map<pair<int,int>,float>::iterator it;

	for (it = sp.m_dictionary.begin(); it != sp.m_dictionary.end();it++){
		sp.m_dictionary[it->first] = sp.m_dictionary[it->first] * n;
	}

	return sp;

}

MatriuSparse MatriuSparse::operator /(const float n){
	if (n == 0)
		throw "Error of vec for /";

	MatriuSparse sp = *this;
	map<pair<int,int>,float>::iterator it;

	for (it = sp.m_dictionary.begin(); it != sp.m_dictionary.end();++it){
		sp.m_dictionary[it->first] = sp.m_dictionary[it->first] / n;
	}

	return sp;
}

ostream& operator<<(ostream &out, MatriuSparse& sp){
	map<pair<int,int>,float>::iterator it;
	out <<"MATRIU DE (FILES: "<<sp.m_dimension <<"  COLUMNES: "<<sp.m_dimension<<" )"<<endl;
	out <<"VALORS (FILA::COL::VALOR)"<<endl;
	pair<int,int> key;

	for (it = sp.m_dictionary.begin(); it != sp.m_dictionary.end();++it){
		if (sp.m_dictionary[it->first] != 0){
			out << "( " <<(it->first).first<<" :: "<<(it->first).second<<" :: "<<it->second<< " ) "<<endl;
		}
	}

	return out;

}

MatriuSparse& MatriuSparse::operator =(const MatriuSparse &m){
	m_noZeroElements = m.m_noZeroElements;
	m_dimension = m.m_dimension;
	m_dictionary = m.m_dictionary;
	m_gradesIn = m.m_gradesIn;
	m_aristas = m.m_aristas;
	return *this;
}

void MatriuSparse::calculaGrau(vector<int> &graus){
	map<int,int>::iterator mapIterator;
	graus.resize(m_gradesIn.size(),0);

	for (mapIterator = m_gradesIn.begin(); mapIterator != m_gradesIn.end(); ++mapIterator){
		graus[mapIterator->first] = mapIterator->second;
	}
}


int MatriuSparse::getMaxNumberOfNodes(string fileName){
	ifstream fileToCheckNodes(fileName);
	int maxValue;
	int other;

	while ( !fileToCheckNodes.eof() ){
		fileToCheckNodes >> maxValue>>other;
	}

	return maxValue;
}
