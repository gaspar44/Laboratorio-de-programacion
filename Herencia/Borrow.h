/*
 * Borrow.h
 *
 *  Created on: 18 oct. 2019
 *      Author: gaspar
 */

#ifndef BORROW_H_
#define BORROW_H_
#include "Data.h"
#include <string>
using namespace std;

class Borrow {
public:
	Borrow() : m_userID("") , m_publicationID(""), m_borrowData(Data()), m_returnData(Data()) {}
	Borrow(string userID, string publicationID,const Data &borrowData,int returnDays);
	Data getReturnData();
	string getUserID();
	string getPublicationID();


private:
	string m_userID;
	string m_publicationID;
	Data m_borrowData;
	Data m_returnData;
};




#endif /* BORROW_H_ */
