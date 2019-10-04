#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

template<class TClau, class TValor>

class Map
{
public:
	Map() : m_longitud(0) {}
	~Map() {};
	int longitud() { return m_longitud; }
	bool esBuit() const { return m_longitud == 0; }
	void afegeix(TClau key,TValor value) { m_keys.push_back(key), m_values.push_back(value), m_longitud++; }
	TValor& operator[] ( const TClau& key );

private:
	int m_longitud;
	vector<TClau> m_keys;
	vector<TValor> m_values;
	TValor m_defaultValue;
};


template<class TClau, class TValor>
TValor& Map<TClau,TValor>::operator [](const TClau& key){
	typename vector<TClau>::iterator it = m_keys.begin();
	int positionIndex = 0;
	bool foundElement = false;

	while(positionIndex < m_longitud){
		string val = *it;
		if (val.compare(key) == 0){
			foundElement = true;
			break;
		}
		positionIndex++;
		it++;
	}

	if (!foundElement)
		return m_defaultValue;

	return m_values.at(positionIndex);

}

