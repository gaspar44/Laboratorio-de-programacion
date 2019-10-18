/*
 * Biblioteca.cpp
 *
 *  Created on: 18 oct. 2019
 *      Author: gaspar
 */

#include "Biblioteca.h"
#include "Book.h"
#include "string"
#include <fstream>
using namespace std;


void Biblioteca::llegirPublicacions(const string & nomFitxer){
	ifstream libraryToCreate(nomFitxer);
	string typeOfPublication;

	while (!libraryToCreate.eof()){
		libraryToCreate>>typeOfPublication;

		if (typeOfPublication.compare("L") == 0){
			string code;
			string name;
			string author;
			int numberOfCopies;
			int daysToBorrow;

			libraryToCreate>>code>>name>>author>>numberOfCopies>>daysToBorrow;

			Book bookToCreate = new Book(code,name,author,numberOfCopies,daysToBorrow);
			m_publications.push_back(bookToCreate);
		}

		else if (typeOfPublication.compare("R") == 0){

		}
	}
}




