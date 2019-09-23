
#include "Racional.h"

NombreRacional::NombreRacional(int numerador,int denominador) {
	m_numerador = numerador;
	m_denominador= denominador;
}

NombreRacional::NombreRacional() {}

NombreRacional::~NombreRacional() {}

//NombreRacional::NombreRacional(NombreRacional &racional) {
//	m_numerador =racional.getNumerador();
//	m_denominador = racional.getDenominador();
//}

int NombreRacional::getNumerador() {
	return m_numerador;
}

int NombreRacional::getDenominador() {
	return m_denominador;
}

void NombreRacional::setNumerador(int numerador) {
	m_numerador = numerador;
}

void NombreRacional::setDenominador(int denominador) {
	m_denominador = denominador;
}

void NombreRacional::simplifica() {
	int otherNumerator = m_numerador;
	int otherDenominator = m_denominador;
	int mcd = mcdCalculator(otherNumerator, otherDenominator);
	int tmp1 = (m_numerador / mcd);
	int tmp2 = (m_denominador / mcd);
	m_numerador = tmp1;
	m_denominador = tmp2;
}
bool NombreRacional::esValid() const {
	return m_denominador != 0;
}

int NombreRacional::mcdCalculator(int numerador,  int denominador)const{
    int t;
    while (numerador > 0){
        t = numerador;
        numerador = denominador % numerador;
        denominador = t;
    }
    return denominador;
}

NombreRacional NombreRacional::operator +(const NombreRacional &r) const {
	int mcm = m_denominador * r.m_denominador;
	int newNumerator = ((mcm/m_denominador) * m_numerador) + ((mcm/r.m_denominador) * r.m_numerador);
	NombreRacional sumOfRacional = NombreRacional(newNumerator,mcm);
	sumOfRacional.simplifica();
	return sumOfRacional;

}

NombreRacional NombreRacional::operator -(const NombreRacional &r) const{
	int mcm = m_denominador * r.m_denominador;
	int newNumerator = ((mcm/m_denominador) * m_numerador) - ((mcm/r.m_denominador) * r.m_numerador);
	NombreRacional sumOfRacional = NombreRacional(newNumerator,mcm);
	sumOfRacional.simplifica();
	return sumOfRacional;

}
NombreRacional NombreRacional::operator *(const NombreRacional &r) const{
	int newDenominador = m_denominador * r.m_denominador;
	int newNumerador = m_numerador * r.m_numerador;
	NombreRacional productOfRacionals = NombreRacional(newNumerador,newDenominador);
	productOfRacionals.simplifica();
	return productOfRacionals;

}

NombreRacional NombreRacional::operator /(const NombreRacional &r) const {
	int newDenominador = m_denominador * r.m_numerador;
	int newNumerador = m_numerador * r.m_denominador;
	NombreRacional divisionOfRacionals = NombreRacional(newNumerador,newDenominador);
	divisionOfRacionals.simplifica();
	return divisionOfRacionals;

}

bool NombreRacional::operator ==(const NombreRacional &r) const {
	NombreRacional tmp1 = NombreRacional(r.m_numerador,r.m_denominador);
	tmp1.simplifica();
	return (m_numerador == tmp1.m_numerador && m_denominador == tmp1.m_denominador);

}



