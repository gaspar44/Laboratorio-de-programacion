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
	MatriuDispersa(string fileName, int rows, int columns);
	MatriuDispersa(int rows, int columns) : SimmetricMatrix(rows,columns) {};
	//MatriuDispersa(const MatriuDispersa& m) { Matriu()
	void init(int rows,int columns)  { SimmetricMatrix::initializeEmptyMatrix(m_matriu,rows,columns); };
	bool getValor(int row,int column,float &value) ;
	void setValor(int row,int column,float value);



private:
};


#endif /* MATRIUDISPERSA_H_ */
