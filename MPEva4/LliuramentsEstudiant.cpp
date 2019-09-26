#include "LliuramentsEstudiant.h"
#include <forward_list>
#include <cstring>

void LliuramentsEstudiant::afegeixTramesa(const string& fitxer, const string& data) {
	Tramesa *tramesa =  new Tramesa(fitxer,data);
	m_trameses.push_front(*tramesa);
}

bool LliuramentsEstudiant::consultaTramesa(const string& data, string& fitxer){
	list<Tramesa>::iterator iterator;
	char *parsedData = stringToChar(data);
	for (iterator = m_trameses.begin(); iterator != m_trameses.end(); ++iterator ){
		char *parsedPurchasedData = stringToChar(iterator->getData());
		if ( strcmp( parsedPurchasedData,parsedData ) == 0){
			fitxer = iterator->getFitxer();
			return true;
		}
	}
	return false;
}

bool LliuramentsEstudiant::eliminaTramesa(const string& data){
	list<Tramesa>::iterator iterator;
	char *parsedData = stringToChar(data);
	for (iterator = m_trameses.begin(); iterator != m_trameses.end();++iterator){
		if (strcmp (stringToChar(iterator->getData()), parsedData) == 0 ){
			iterator = m_trameses.erase(iterator);
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

//void LliuramentsEstudiant::realDelete(list<Tramesa>::iterator iterator,const char *parsedData){
//	list<Tramesa> copyList;
//	list<Tramesa>::iterator it;
//
//
//	for (it = m_trameses.begin(); it != m_trameses.end();++it) {
//		if ((strcmp(stringToChar(iterator->getData()), parsedData) != 0 )){
//			Tramesa tramesaToCopy = m_trameses.front();
//			copyList.push_front(tramesaToCopy);
//			if (!m_trameses.empty()){
//				m_trameses.pop_front();
//			}
//
//		}
//		else
//			it = m_trameses.erase(iterator);
//	}
//
//	m_trameses = copyList;

// }
