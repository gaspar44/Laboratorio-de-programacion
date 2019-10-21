/*
 * Book.cpp
 *
 *  Created on: 18 oct. 2019
 *      Author: gaspar
 */

#include "Book.h"
#include "Publicacio.h"

Book::Book(string publicationID,string title,string author,int numberOfCopies,int daysToBorrow) : Publicacio(title, publicationID, daysToBorrow,numberOfCopies){
	m_author = author;
}



