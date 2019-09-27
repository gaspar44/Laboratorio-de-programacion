#include "Matriu.h"
#include <cmath>

void Matriu::resize(int nFiles,int nColumnes){
	/*
	 * Recordando que las matrices son un arreglo de apuntadores
	 * y que los apuntadores tienen otro arreglo, se procede a iniciar
	 * el primer arreglo
	 */
	int **newMatrix = new int*[nFiles];

	for (int i = 0; i < nColumnes; i++){
		int *newColumn = new int[nColumnes];
		newMatrix[i] = newColumn;
	}

	if (esBuida()) {
		initializeEmptyMatrix(newMatrix,nFiles, nColumnes);
		return;
	}


}

void Matriu::initializeEmptyMatrix(int** matrix,int nFiles, int nColumnes){
	for(int i = 0; i < nFiles; i++){
		int *temp = matrix[i];

		for (int j = 0 ; j < nColumnes; j++){
			temp[j] = 0;
		}
	}

	m_nColumnes = nColumnes;
	m_nFiles = nFiles;
	m_matriu = matrix;
}
