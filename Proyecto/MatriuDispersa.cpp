/*
 * MatriuDispersa.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: gaspar
 */

#include "MatriuDispersa.h"
#include <iostream>
#include <fstream>

MatriuDispersa::MatriuDispersa(string fileName) {
	m_matriu = nullptr;
	int rowToWrite;
	int columnToWrite;
	int rowsAndColumnsToReserve = getMaxNumberOfNodes(fileName) + 1;

	resize(rowsAndColumnsToReserve, rowsAndColumnsToReserve);


	ifstream fileToCreateMatrix(fileName);
	string readedLine;


	while(!fileToCreateMatrix.eof()){
		fileToCreateMatrix>>rowToWrite>>columnToWrite;
		setValor(rowToWrite, columnToWrite, 1);
	}

}

MatriuDispersa::MatriuDispersa(const MatriuDispersa &m) : SimmetricMatrix(m){}


int MatriuDispersa::getMaxNumberOfNodes(string fileName){
	ifstream fileToCheckNodes(fileName);
	int maxValue;
	int other;

	while ( !fileToCheckNodes.eof() ){
		fileToCheckNodes >> maxValue>>other;
	}
	return maxValue;

}
