#include "Matriu.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

Matriu::~Matriu(){
	releaseMatrixMemory();
}

void Matriu::resize(int nFiles,int nColumnes){
	/*
	 * Recordando que las matrices son un arreglo de apuntadores
	 * y que los apuntadores tienen otro arreglo, se procede a iniciar
	 * el primer arreglo
	 */
	float **newMatrix = new float*[nFiles];

	for (int i = 0; i < nColumnes; i++){
		float *newColumn = new float[nColumnes];
		newMatrix[i] = newColumn;
	}

	if (esBuida()) {
		initializeEmptyMatrix(newMatrix,nFiles, nColumnes);
	}

	for(int i = 0; i < nFiles; i++) {
		float *temp = newMatrix[i];

		for (int j = 0; j < nColumnes; j++){
			if (j >= nColumnes){
				temp[j] = m_matriu[i][j];
			}
			else {
				temp[j] = 0;
			}
		}
	}

	releaseMatrixMemory();

	m_nColumnes = nColumnes;
	m_nFiles = nFiles;
	m_matriu = newMatrix;

}

void Matriu::transpose() {
	int newFiles = m_nColumnes;
	int newColumnes = m_nFiles;
	float **transposeMatrix = new float*[m_nFiles];

	for (int i = 0; i < m_nColumnes; i++){
		float *newColumn = new float[m_nColumnes];
		transposeMatrix[i] = newColumn;
	}

	for (int i = 0 ; i < m_nFiles; i++) {
		for(int j = 0; j < m_nColumnes; j++) {
			transposeMatrix[j][i] = m_matriu[i][j];
		}
	}

	releaseMatrixMemory();
	m_matriu = transposeMatrix;
	m_nColumnes = newColumnes;
	m_nFiles = newFiles;
}

Matriu& Matriu::operator =(const Matriu& m) {
	m_nColumnes = m.m_nColumnes;
	m_nFiles = m.m_nFiles;
	float **copyMatrix = new float* [m_nFiles];

	for (int i = 0; i < m_nColumnes; i++){
		float *newColumn = new float[m_nColumnes];
		copyMatrix[i] = newColumn;
	}

	for(int i = 0; i < m_nFiles; i++){
		for (int j = 0; j < m_nColumnes; j++) {
			copyMatrix[i][j] = m.m_matriu[i][j];
		}
	}

	m.~Matriu();

	m_matriu = copyMatrix;
	return *this;
}
void Matriu::setValor(int fila,int columna,float valor){
	try {
		m_matriu[fila][columna];
	}
	catch (const std::out_of_range& oor) {
		std::cout<<"index out of range i: "<<fila<<" j: "<<columna<<std::endl;
	}

	m_matriu[fila][columna] = valor;
}

float Matriu::getValor(int fila,int columna) const{
	return m_matriu[fila][columna];
}

Matriu Matriu::operator+(const Matriu& m){
	if (m_nColumnes != m.getNColumnes() || m_nFiles != m.getNFiles()){
		return Matriu(0,0);
	}

	Matriu sumMatrix = Matriu(m_nFiles,m_nColumnes);

	for (int i = 0; i < m_nFiles ; i ++){
		for(int j = 0 ; j < m_nColumnes;j++){
			sumMatrix.m_matriu[i][j] = m_matriu[i][j] +m.m_matriu[i][j];
		}
	}
	return sumMatrix;
}

Matriu Matriu::operator +(const float s){
	Matriu constSumMatrix = *this;

	for (int i = 0; i < constSumMatrix.m_nFiles; i++){
		for(int j = 0; j < constSumMatrix.m_nColumnes;j++){
			constSumMatrix.m_matriu[i][j] = constSumMatrix.m_matriu[i][j] + s;
		}
	}
	return constSumMatrix;
}

bool Matriu::operator ==(const Matriu& m){
	if (m_nColumnes != m.getNColumnes() || m_nFiles != m.getNFiles()){
		return false;
	}

	for (int i = 0; i < m_nFiles; i++){
		for (int j = 0; j < m_nColumnes; j++){

			if (m_matriu[i][j] != m.m_matriu[i][j])
				return false;
		}

	}

	return true;
}

void Matriu::releaseMatrixMemory() {
	for (int i = 0; i < m_nFiles; i++) {
		if (m_matriu[i] != 0)
			delete [] m_matriu[i];
	}

	if (m_matriu != 0)
		delete[] m_matriu;
}

void Matriu::initializeEmptyMatrix(float** matrix,int nFiles, int nColumnes){
	for(int i = 0; i < nFiles; i++){
		float *temp;
		if (matrix[i] != nullptr) {
			temp = matrix[i];
		}
		else {
			temp = new float[m_nFiles];
		}

		for (int j = 0 ; j < nColumnes; j++){
			temp[j] = 0;
		}
	}

}
