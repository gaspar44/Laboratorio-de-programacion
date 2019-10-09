#include "Persona.h"

ostream& operator<<(ostream &out, const Persona& p)
{
	out << "(" << p.getNom() << ", " << p.getEdat() << ")";
	return out;
}

bool Persona::operator ==(Persona &p){
	return ((m_nom.compare(p.m_nom) == 0) && m_edat == p.m_edat);
}

