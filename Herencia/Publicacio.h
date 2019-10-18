/*
 * Publicacio.h
 *
 *  Created on: 18 oct. 2019
 *      Author: gaspar
 */

#ifndef PUBLICACIO_H_
#define PUBLICACIO_H_
#include <string>
using namespace std;

class Publicacio {
public:
	Publicacio() : m_userID("") , m_publicationID("") , m_daysToBorrow(0) {} ;
	Publicacio(string userID, string publicationID, int daysToBorrow) :  m_userID(userID), m_publicationID(publicationID), m_daysToBorrow(daysToBorrow) {}

protected:
	string m_userID;
	string m_publicationID;
	int m_daysToBorrow;
};





#endif /* PUBLICACIO_H_ */
