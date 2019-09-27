#include "Exercici.h"
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string.h>
using namespace std;

Exercici::Exercici(const Exercici &e) {
	m_descripcio = e.m_descripcio;
	m_dataLimit = e.m_dataLimit;
	m_nEstudiants = e.m_nEstudiants;
	m_lliuraments = new LliuramentsEstudiant[m_nEstudiants];

	for (int i = 0; i < m_nEstudiants;i++) {
		m_lliuraments[i] = e.m_lliuraments[i];
	}

}

Exercici::~Exercici() {}

void Exercici::inicialitzaEstudiants(const string &fitxerEstudiants){
	ifstream infile(fitxerEstudiants);
	string line;
	int counter = 0;
	bool firstTime = true;
	getline(infile,line);
	istringstream stringToIntegerParser(line);

	if (!(stringToIntegerParser >> m_nEstudiants)) {
		perror("error to read number of students\n");
		exit(EXIT_FAILURE);
	}

	m_lliuraments = new LliuramentsEstudiant[m_nEstudiants];

	while (getline(infile,line)) {
		LliuramentsEstudiant lliurament = LliuramentsEstudiant();
		lliurament.setNiu(line);
		m_lliuraments[counter] = lliurament;
		counter = counter + 1;
	}

	infile.close();
}

bool Exercici::afegeixTramesa(const string& niu,const string& fitxer, const string& data){
	int parsedNiu = stoi(niu);

	for (int i = 0; i < m_nEstudiants;i++) {
		int parsedLliuramentNiu = stoi(m_lliuraments[i].getNiu());
		if (parsedLliuramentNiu == parsedNiu){
			m_lliuraments[i].afegeixTramesa(fitxer,data);
			return true;
		}
	}
	return false;
}


bool Exercici::consultaTramesa(const string& niu, const string& data, string& fitxer){
	int parsedNiu = stoi(niu);

	for (int i = 0;i < m_nEstudiants;i++) {
		int parsedLliuramentNiu = stoi(m_lliuraments[i].getNiu());
		if (parsedLliuramentNiu == parsedNiu)
			return m_lliuraments[i].consultaTramesa(data, fitxer);
	}
	return false;
}

bool Exercici::eliminaTramesa(const string& niu, const string& data){
	int parsedNiu;
	try {
		parsedNiu = stoi(niu);

	} catch (const std::invalid_argument& e){
		return false;
	}

	for (int i = 0 ; i < m_nEstudiants; i++){
		int parsedLliuramentNiu = stoi(m_lliuraments[i].getNiu());
		if (parsedLliuramentNiu == parsedNiu)
			return m_lliuraments[i].eliminaTramesa(data);
	}
	return false;
}
Exercici& Exercici::operator =(const Exercici &e){
	Exercici *exercici = new Exercici(e.m_descripcio,e.m_dataLimit);
	exercici->m_nEstudiants = e.m_nEstudiants;
	exercici->m_lliuraments = e.m_lliuraments;
	return *exercici;
}
