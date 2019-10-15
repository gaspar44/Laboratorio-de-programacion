/*
 * MatriuDispersa.h
 *
 *  Created on: 14 oct. 2019
 *      Author: gaspar
 */

#ifndef MATRIUDISPERSA_H_
#define MATRIUDISPERSA_H_
#include "Matriu.h"
#include <string>
using namespace std;

class MatriuDispersa : public Matriu {
public:
	MatriuDispersa() : Matriu() {};
	MatriuDispersa(string fileName, int rows, int columns);
	MatriuDispersa(int rows, int columns) : Matriu(rows,columns) {};
	//MatriuDispersa(const MatriuDispersa& m) { Matriu()
	void init(int rows,int columns)  { Matriu::initializeEmptyMatrix(m_matriu,rows,columns); };
	bool getValor(int row,int column,float &value) ;
	void setValor(int row,int column,float value);



private:
};


#endif /* MATRIUDISPERSA_H_ */
