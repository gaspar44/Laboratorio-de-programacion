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
	Publicacio() : m_title("") , m_publicationID("") , m_daysToBorrow(0) , m_numberOfCopies(0) {} ;
	Publicacio(string title, string publicationID, int daysToBorrow,int numberOfCopies) :  m_title(title), m_publicationID(publicationID), m_daysToBorrow(daysToBorrow) ,m_numberOfCopies(numberOfCopies){}
	string getPublicationID() { return m_publicationID ; }
	int getNumberOfCopies() { return m_numberOfCopies ; }
	int getDaysToBorrow() { return m_daysToBorrow; }
	void decreaseCopy() { m_numberOfCopies = m_numberOfCopies - 1 ;};
	void increaseCopy() { m_numberOfCopies = m_numberOfCopies + 1 ;};

protected:
	string m_title;
	string m_publicationID;
	int m_daysToBorrow;
	int m_numberOfCopies;
};





#endif /* PUBLICACIO_H_ */
