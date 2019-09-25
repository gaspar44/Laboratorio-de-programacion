#include "LliuramentsEstudiant.h"
#include <forward_list>
#include <cstring>


void LliuramentsEstudiant::afegeixTramesa(const string& fitxer, const string& data) {
	Tramesa *tramesa =  new Tramesa(fitxer,data);
	m_trameses.push_front(*tramesa);
}

bool LliuramentsEstudiant::consultaTramesa(const string& data, string& fitxer){
	list<Tramesa>::iterator iterator;
	char * parsedData = stringToChar(data);
	for (iterator = m_trameses.begin(); iterator != m_trameses.end(); iterator++ ){
		if ( strcmp( stringToChar( iterator->getData()),parsedData ) == 0){
			if (strcmp(stringToChar(iterator->getFitxer()),stringToChar(fitxer)) == 0)
				return true;

			return false;
		}
	}
	return false;
}

bool LliuramentsEstudiant::eliminaTramesa(const string& data){
	list<Tramesa>::iterator iterator;
	char *parsedData = stringToChar(data);
	for (iterator = m_trameses.begin(); iterator != m_trameses.end();iterator++){
		if (strcmp (stringToChar(iterator->getData()), parsedData) == 0 ){
			m_trameses.erase(iterator);
			return true;
		}
	}
	return false;
}

char* LliuramentsEstudiant::stringToChar(string stringToParse){
	int stringSize = stringToParse.length();
	char * array = new char[stringSize + 1];
	strcpy(array, stringToParse.c_str());
	return array;
}
