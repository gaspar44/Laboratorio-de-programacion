#include "Persona.h"

ostream& operator<<(ostream &out, const Persona& p)
{
	out << "(" << p.m_nom << ", " << p.m_edat << ")";
	return out;
}

bool Persona::operator ==(const Persona &p){
	return ((m_nom.compare(p.m_nom) == 0) && m_edat == p.m_edat);
}

