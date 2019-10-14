/*
 * MatriuDispersa.cpp
 *
 *  Created on: 14 oct. 2019
 *      Author: gaspar
 */

#include "MatriuDispersa.h"
#include <iostream>
#include <fstream>

MatriuDispersa::MatriuDispersa(string fileName,int rows,int columns){
	Matriu::Matriu(rows,columns);
	ifstream fileToCreateMatrix(fileName);
	string readedLine;

	while(getline(fileToCreateMatrix,readedLine)){

	}

}

