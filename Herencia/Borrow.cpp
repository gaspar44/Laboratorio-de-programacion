/*
 * Borrow.cpp
 *
 *  Created on: 18 oct. 2019
 *      Author: gaspar
 */
#include "Borrow.h"

Borrow::Borrow(string userID,string publicationID, const Data& borrowData,int returnDays){
	m_userID = userID;
	m_publicationID = publicationID;
	m_borrowData = borrowData;
	m_returnData = borrowData + returnDays;
}

string Borrow::getPublicationID(){
	return m_publicationID;
}

string Borrow::getUserID(){
	return m_userID;
}

Data Borrow::getReturnData() {
	return m_returnData;
}
