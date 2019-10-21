/*
 * Magazine.cpp
 *
 *  Created on: 18 oct. 2019
 *      Author: gaspar
 */
#include "Magazine.h"

Magazine::Magazine(string codeID,string title,string periocidad,int numberOfCopies,int numberOfExamples ) :
Publicacio(title, codeID,30,numberOfCopies) {
	m_periocidad = periocidad;

	for (int i = 0; i < m_numberOfCopies;i++){
		m_numberOfExamples.push_back(numberOfExamples + i);
	}
}

