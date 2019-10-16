/*
 * MatriuDispersa.h
 *
 *  Created on: 14 oct. 2019
 *      Author: gaspar
 */

#ifndef MATRIUDISPERSA_H_
#define MATRIUDISPERSA_H_
#include <string>

#include "SimmetricMatrix.h"
using namespace std;

class MatriuDispersa : public SimmetricMatrix {
public:
	MatriuDispersa() : SimmetricMatrix() {};
	MatriuDispersa(string fileName);
	MatriuDispersa(int rows, int columns) : SimmetricMatrix(rows,columns) {};
	MatriuDispersa(const MatriuDispersa& m);
	void init(int rows,int columns)  { SimmetricMatrix::initializeEmptyMatrix(m_matriu,rows,columns); };
	bool getValor(int row,int column,float &value) { return SimmetricMatrix::getValor(row, column, value); };
	void setValor(int row,int column,float value) { SimmetricMatrix::setValor(m_matriu, row, column, value); } ;



private:
	int getMaxNumberOfNodes(string fileName);
};


#endif /* MATRIUDISPERSA_H_ */
