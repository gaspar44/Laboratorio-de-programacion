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
	Map<TClau,TValor>(const Map<TClau,TValor>& m);
	int longitud() const { return m_longitud; }
	bool esBuit() const { return m_longitud == 0; }
	void afegeix(TClau key,TValor value);
	TValor& operator[] ( const TClau& key );


	const TValor& operator[](const TClau& clau);
	const TClau& operator[]( const TValor& value );
	TClau& operator[] ( const int indexToGet);
	const TClau& operator[](const int& indexToGet) const;
	Map<TClau,TValor>& operator=(const Map<TClau,TValor>& m);

private:
	int m_longitud;
	vector<TClau> m_keys;
	vector<TValor> m_values;
	TValor m_defaultValue;
	TClau m_defaultKey;

};

template<class TClau, class TValor>
void Map<TClau,TValor>::afegeix(TClau key,TValor value){
	typename vector<TClau>::iterator it = m_keys.begin();
	int positionIndex = 0;

	while(positionIndex < m_longitud){
		if (*it == key){
			m_values[positionIndex] = value;
			return;
		}
		positionIndex++;
		it++;
	}

	m_keys.push_back(key);
	m_values.push_back(value);
	m_longitud++;

}


template<class TClau, class TValor>
Map<TClau,TValor>::Map(const Map<TClau,TValor>& m){
	m_longitud = m.m_longitud;

	for (int i = 0 ; i < m.m_longitud; i++){
		m_keys.push_back(m.m_keys[i]);
		m_values.push_back(m.m_values[i]);
	}

}

template<class TClau, class TValor>
Map<TClau,TValor>& Map<TClau,TValor>::operator=(const Map<TClau,TValor>& m){
	m_longitud = m.m_longitud;

	for (int i = 0 ; i < m.m_longitud; i++){
		m_keys.push_back(m.m_keys[i]);
		m_values.push_back(m.m_values[i]);
	}

	return *this;
}

template<class TClau, class TValor>
TValor& Map<TClau,TValor>::operator [](const TClau& key){
	typename vector<TClau>::iterator it = m_keys.begin();
	int positionIndex = 0;
	bool foundElement = false;

	while(positionIndex < m_longitud){
		if (*it == key){
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

template<class TClau, class TValor>
const TValor& Map<TClau,TValor>::operator[](const TClau& key){
	typename vector<TClau>::iterator it = m_keys.begin();
	int positionIndex = 0;
	bool foundElement = false;

	while(positionIndex < m_longitud){
		if (*it == key){
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

template<class TClau, class TValor>
const TClau& Map<TClau,TValor>::operator [](const TValor& value){
	typename vector<TValor>::iterator it = m_values.begin();
	int positionIndex = 0;
	bool foundElement = false;

	while(positionIndex < m_longitud){
		if (*it == value){
			foundElement = true;
			break;
		}
		positionIndex++;
		it++;
	}

	if (!foundElement)
		return m_defaultKey;

	return m_keys.at(positionIndex);

}



template<class TClau,class TValor>
TClau& Map<TClau,TValor>::operator [] ( const int indexToGet){
	if (indexToGet < 0 || indexToGet > m_longitud)
		return m_defaultKey;

	return m_keys.at(indexToGet);

}

template<class TClau,class TValor>
const TClau& Map<TClau,TValor>::operator [] ( const int& indexToGet) const {
	if (indexToGet < 0 || indexToGet > m_longitud)
		return m_defaultKey;

	return m_keys.at(indexToGet);
}
