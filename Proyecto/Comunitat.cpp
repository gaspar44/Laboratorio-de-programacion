/*
 * Comunitats.cpp
 *
 *  Created on: 2 dic. 2019
 *      Author: gaspar
 */
#include "Comunitat.h"

Comunitat::Comunitat(MatriuSparse* pMAdj) {
	m_sparseMatrix = pMAdj;
	m_primComdeltaQ = 0;
	calculaM2();
	calculaK();
	calculaA();


}


