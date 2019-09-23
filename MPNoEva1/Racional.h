#ifndef RACIONAL_H
#define RACIONAL_H
class NombreRacional
{
public:
	NombreRacional();
	NombreRacional(int numerador,int denominador);
	~NombreRacional();
//	NombreRacional(NombreRacional &racional);
	void setNumerador(int numerador);
	void setDenominador(int denominador);
	int getNumerador();
	int getDenominador();
	bool esValid() const;
	void simplifica();
	NombreRacional operator +(const NombreRacional& r) const;
	NombreRacional operator -(const NombreRacional& r) const;
	NombreRacional operator *(const NombreRacional& r) const;
	NombreRacional operator /(const NombreRacional& r) const;
	bool operator ==(const NombreRacional& r) const;

private:
	int m_numerador;
	int m_denominador;
	int mcdCalculator(int numerador, int denominador) const;
};

#endif
