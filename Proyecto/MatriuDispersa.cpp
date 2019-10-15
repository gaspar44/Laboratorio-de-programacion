/*
 * MatriuDispersa.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: gaspar
 */

#include "MatriuDispersa.h"
#include <iostream>
#include <fstream>

MatriuDispersa::MatriuDispersa(string fileName,int rows,int columns) : Matriu(rows, columns){
	ifstream fileToCreateMatrix(fileName);
	string readedLine;

	while(getline(fileToCreateMatrix,readedLine)){

	}

}

bool MatriuDispersa::getValor(int row,int column,float &value){
	if (row > m_nFiles || column > m_nColumnes)
		return false;

	std::cout<<row<<std::endl;
	std::cout<<column<<std::endl;
	value = row > column ? m_matriu[column][row - column] : m_matriu[row][column - row];

	return true;
}

void MatriuDispersa::setValor(int row,int column,float value){
	if (value == 0)
		return;

	if (row > column) {
		m_matriu[column][row - column] = value;
	}

	else {
		m_matriu[row][column - row] = value;
	}

}

