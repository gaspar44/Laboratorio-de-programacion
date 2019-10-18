#pragma once
#include "Publicacio.h"
#include "Data.h"
#include "Borrow.h"
#include <string>
#include <vector>

using namespace std;

class Biblioteca
{
public:
	Biblioteca() {}
	~Biblioteca() {}

	void llegirPublicacions(const string& nomFitxer);
	bool prestar(const string& idUsuari, const string& codi, const Data& dataPrestec, Data& dataRetorn, int nExemplar = 0);
	bool retornar(const string& idUsuari, const string& codi, const Data& data, bool &dataCorrecta, int nExmplar = 0);

private:
	vector<Publicacio> m_publications;
	vector<Borrow> m_borrows;
};

