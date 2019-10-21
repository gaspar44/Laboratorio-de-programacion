/*
 * Book.h
 *
 *  Created on: 18 oct. 2019
 *      Author: gaspar
 */

#ifndef BOOK_H_
#define BOOK_H_
#include "Publicacio.h"
#include <string>
using namespace std;

class Book : public Publicacio {
public:
	Book() : Publicacio() ,m_author("") {};
	Book(string codeID,string title,string author,int numberOfCopies,int daysToBorow);

private:
	string m_author;

};




#endif /* BOOK_H_ */
