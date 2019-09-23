#include "Operacions.h"
#include <iostream>

using namespace std;

const int NPROVES = 7;

void mostraBool(bool logic)
{
	if (logic)
		cout << "TRUE";
	else
		cout << "FALSE";
}

float testOperarNombreRacional()
{
	float reduccio = 0.0;

	int racional1[2][NPROVES] =
	{
		{ 1, 4, 6, 8, 1, 4, 3 },
		{ 2, 5, 6, 0, 8, 10, 4}
	};

	int racional2[2][NPROVES] =
	{
		{ 2, 8, 3, 2, 3, 2, 1 },
		{ 1, 0, 6, 4, 8, 10, 9 },
	};

	char operacio[NPROVES] = { '+', '+', '-', '-', '/', '*', ';' };
	bool validEsperat[NPROVES] = { true, false, true, false , true, true, false };

	int resultatEsperat[2][NPROVES] =
	{ 
		{ 5, 0, 1, 0, 1, 2, 0 },
		{ 2, 0, 2, 0, 3, 25, 0 }
	};

	cout << endl;
	cout << "Comment :=>> Iniciant test funcio OPERAR" << endl;
	cout << "Comment :=>> ===========================" << endl;
	
	for (int p = 0; p < NPROVES; p++)
	{
		NombreRacional r1(racional1[0][p], racional1[1][p]);
		NombreRacional r2;
		r2.setNumerador(racional2[0][p]);
		r2.setDenominador(racional2[1][p]);
		NombreRacional racionalEsperat(resultatEsperat[0][p], resultatEsperat[1][p]);
		cout << "Comment :=>> ------------------------------------------" << endl;
		cout << "Comment :=>> TEST " << p+1  << endl;
		cout << "Comment :=>> Nombre 1: " << r1.getNumerador() << "/" << r1.getDenominador() << endl;
		cout << "Comment :=>> Nombre 2: " << r2.getNumerador() << "/" << r2.getDenominador() << endl;
		cout << "Comment :=>> Operacio: " << operacio[p] << endl;
		cout << "Comment :=>> ---" << endl;
		cout << "Comment :=>> Valor retorn esperat: "; mostraBool(validEsperat[p]); cout << endl;
		if (validEsperat[p])
			cout << "Comment :=>> Resultat esperat: " << racionalEsperat.getNumerador() << "/" << racionalEsperat.getDenominador() << endl;
		cout << "Comment :=>> ---" << endl;
		NombreRacional resultat;
		bool valid = operar(r1, r2, operacio[p], resultat);
		cout << "Comment :=>> Valor retorn obtingut: "; mostraBool(valid); cout << endl;
		if (valid)
			cout << "Comment :=>> Resultat obtingut: " << resultat.getNumerador() << "/" << resultat.getDenominador() << endl;
		if (valid == validEsperat[p])
		{
			if (valid)
			{
				if (resultat == racionalEsperat)
					cout << "Comment :=>> CORRECTE" << endl;
				else
				{
					cout << "Comment :=>> ERROR" << endl;
					reduccio += 2.0;
				}
			}
			else
				cout << "Comment :=>> CORRECTE" << endl;
		}
		else
		{
			cout << "Comment :=>> ERROR" << endl;
			reduccio += 2.0;
		}
	}
	return reduccio;
}

int main()
{
	float grade = 10.0;

	grade -= testOperarNombreRacional();

	if (grade < 0)
		grade = 0.0;
	cout << "Comment :=>> ------------------------------------------" << endl;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;

	return 0;
}