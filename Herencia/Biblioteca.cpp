/*
 * Biblioteca.cpp
 *
 *  Created on: 18 oct. 2019
 *      Author: gaspar
 */

#include "Biblioteca.h"
#include <string.h>
#include <fstream>
using namespace std;


void Biblioteca::llegirPublicacions(const string & nomFitxer){
	ifstream libraryToCreate(nomFitxer);
	string typeOfPublication;
	string readedLine;

	while (!libraryToCreate.eof()){
		getline(libraryToCreate, typeOfPublication);
		string publicationID;
		string title;
		string numberOfCopies;

		if (typeOfPublication.compare("L") == 0){

			string author;
			string daysToBorrow;
			getline(libraryToCreate,publicationID);
			getline(libraryToCreate,title);
			getline(libraryToCreate,author);
			getline(libraryToCreate, numberOfCopies);
			getline(libraryToCreate,daysToBorrow);

			int numberOfcopies = stoi(numberOfCopies.c_str());
			int daysToborrow = stoi(daysToBorrow.c_str());

			Book *bookToCreate = new Book(publicationID, title, author, numberOfcopies, daysToborrow);
			m_publications.push_back(*bookToCreate);
		}

		else if (typeOfPublication.compare("R") == 0){
			string periocidad;
			string numberOfExamples;

			getline(libraryToCreate,publicationID);
			getline(libraryToCreate,title);
			getline(libraryToCreate,periocidad);
			getline(libraryToCreate,numberOfCopies);
			getline(libraryToCreate,numberOfExamples);

			int numberOfcopies = stoi(numberOfCopies.c_str());

			char cp = numberOfExamples[0];
			int intergerNumberOfExamples = atoi(&cp);

			Magazine *magazineToCreate = new Magazine(publicationID,title,periocidad,numberOfcopies,intergerNumberOfExamples);
			m_publications.push_back(*magazineToCreate);

		}
	}
}

bool Biblioteca::prestar(const string& idUsuari, const string& codi, const Data& dataPrestec, Data& dataRetorn, int nExemplar) {
	vector<Publicacio>::iterator it;

	for (it = m_publications.begin(); it != m_publications.end();++it){
		if (codi.compare( it->getPublicationID() ) == 0 && it->getNumberOfCopies() != 0){
			it->decreaseCopy();
			Borrow borrow = Borrow( idUsuari, it-> getPublicationID(), dataPrestec, it->getDaysToBorrow() );
			m_borrows.push_back(borrow);
			dataRetorn = borrow.getReturnData();
			return true;
		}
	}

	return false;
}


bool Biblioteca::retornar(const string& idUsuari, const string& codi, const Data& data, bool &dataCorrecta, int nExmplar){
	vector<Borrow>::iterator it;


	for (it = m_borrows.begin();it != m_borrows.end();++it){
		dataCorrecta = data < it->getReturnData();

		if (idUsuari.compare(it->getUserID()) == 0 && codi.compare(it->getPublicationID()) == 0) {
			m_borrows.erase(it);
			return true;
		}
	}
	return false;

}
