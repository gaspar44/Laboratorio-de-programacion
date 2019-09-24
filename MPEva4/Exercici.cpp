#include "Exercici.h"
#include <fstream>
#include <stdlib.h>
#include <sstream>
using namespace std;

Exercici::Exercici(const Exercici &e) {
	m_descripcio = e.m_descripcio;
	m_dataLimit = e.m_dataLimit;
	m_lliuraments = e.m_lliuraments;
	m_nEstudiants = e.m_nEstudiants;
}

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
	for (int i = 0; i < m_nEstudiants;i++) {
		if (m_lliuraments[i].m_niu == niu){
			m_lliuraments[i].afegeixTramesa(fitxer,data);
			return true;
		}
	}
	return false;
}
