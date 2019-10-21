/*
 * Magazine.h
 *
 *  Created on: 18 oct. 2019
 *      Author: gaspar
 */

#ifndef MAGAZINE_H_
#define MAGAZINE_H_
#include "Publicacio.h"
#include <vector>
#include <string>
using namespace std;

class Magazine : public Publicacio {
public:
	Magazine() : Publicacio() , m_periocidad("") {}
	Magazine(string codeID,string title,string periocidad,int numberOfCopies,int numberOfExamples );

private:
	string m_periocidad;
	vector<int> m_numberOfExamples;


};




#endif /* MAGAZINE_H_ */
