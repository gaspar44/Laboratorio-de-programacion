#include "Operacions.h"
#include <string.h>

bool operar(const NombreRacional &r1, const NombreRacional &r2, char operacio, NombreRacional &resultat)
{

	if (!r1.esValid() || !r2.esValid()) {
		return false;
	}

	if (operacio == '+') {
		resultat = r1 + r2;
	}

	else if ( operacio == '-') {
		resultat = r1 - r2;
	}

	else if (operacio == '*') {
		resultat = r1 * r2;
	}

	else if (operacio == '/') {
		resultat = r1 / r2;
	}
	else {
		return false;
	}
	return true;
}

