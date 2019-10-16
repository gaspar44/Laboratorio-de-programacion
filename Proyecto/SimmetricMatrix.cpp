#include "SimmetricMatrix.h"

#include <stdexcept>
#include <iostream>
#include <cmath>

SimmetricMatrix::~SimmetricMatrix(){
//	releaseMatrixMemory();
}

void SimmetricMatrix::resize(int nFiles,int nColumnes){
	/*
	 * Recordando que las matrices son un arreglo de apuntadores
	 * y que los apuntadores tienen otro arreglo, se procede a iniciar
	 * el primer arreglo
	 */
	float **newMatrix = new float* [nFiles];

	for (int i = 0; i < nFiles; i++){
		float *newColumn = new float[nColumnes-i];
		newMatrix[i] = newColumn;
	}

	if (esBuida()) {
		initializeEmptyMatrix(newMatrix,nFiles, nColumnes);
	}

	else {
		if (m_nFiles > nFiles && m_nColumnes > nColumnes){
			fillNewMatrixWithOld(m_matriu,newMatrix, nFiles, nColumnes);
		}
		else if (m_nFiles <= nFiles && m_nColumnes <= nColumnes){
			initializeEmptyMatrix(newMatrix, nFiles, nColumnes);
			fillNewMatrixWithOld(m_matriu,newMatrix, m_nFiles, m_nColumnes);
		}

	}

	releaseMatrixMemory();

	m_nColumnes = nColumnes;
	m_nFiles = nFiles;
	m_matriu = newMatrix;
}


SimmetricMatrix& SimmetricMatrix::operator =(const SimmetricMatrix& m) {
	m_nColumnes = m.m_nColumnes;
	m_nFiles = m.m_nFiles;
	float **copyMatrix = new float* [m_nFiles];

	for (int i = 0; i < m_nFiles; i++){
		float *newColumn = new float[m_nColumnes-1];
		copyMatrix[i] = newColumn;
	}

	fillNewMatrixWithOld(m.m_matriu,copyMatrix, m.m_nFiles, m.m_nColumnes);

	m_matriu = copyMatrix;
	return *this;
}

void SimmetricMatrix::setValor(float**matrix,int row,int column,float value){
	if (value == 0)
		return;

	if (row > column) {
		matrix[column][row - column] = value;
	}

	else {
		matrix[row][column - row] = value;
	}
}

void SimmetricMatrix::setValor(int row,int column,float value){
	setValor(m_matriu, row, column, value);
}


bool SimmetricMatrix::getValor(int row,int column,float &value) const{
	if (row > m_nFiles || column > m_nColumnes)
		return false;

	value = row > column ? m_matriu[column][row - column] : m_matriu[row][column - row];

	return true;
}

void SimmetricMatrix::releaseMatrixMemory() {
	for (int i = 0; i < m_nFiles; i++) {
		if (m_matriu[i] != 0)
			delete [] m_matriu[i];
	}

	if (m_matriu != 0)
		delete[] m_matriu;
}

void SimmetricMatrix::initializeEmptyMatrix(float** matrix,int nFiles, int nColumnes){
	for (int i = 0; i < nFiles;i++){
		for(int j = 0; j < nColumnes;j++){
			setValor(matrix,i, j, 0);
		}
	}
}

void SimmetricMatrix::fillNewMatrixWithOld(float **sourceMatrix,float **destinyMatrix, int rowLimiter,int columnLimiter){
	for (int i = 0; i < rowLimiter;i++){
		float *temp = destinyMatrix[i];
		for (int j = 0; j < columnLimiter; j++){
			temp[j] = sourceMatrix[i][j];

		}
	}
}
