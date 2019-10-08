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
	Map<TClau,TValor>(const Map<TClau,TValor>& m){
		m_longitud = m.m_longitud;

		for (int i = 0 ; i < m.m_longitud; i++){
			m_keys.push_back(m.m_keys[i]);
			m_values.push_back(m.m_values[i]);
		}

	}
	int longitud() const { return m_longitud; }
	bool esBuit() const { return m_longitud == 0; }
	void afegeix(TClau key,TValor value){
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

	const TValor& operator[](const TClau& key){
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

	const TClau& operator[]( const TValor& value ){
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

	const TClau& operator[](const int& indexToGet) const{
		if (indexToGet < 0 || indexToGet > m_longitud)
			return m_defaultKey;

		return m_keys.at(indexToGet);
	}

	TClau& operator[] ( const int indexToGet){
		return (const_cast<const Map&>(*this))[indexToGet];
	}

	TClau& operator[]( const TValor& value ){
		return (const_cast<const Map&>(*this))[value];
	}

	TValor& operator[] ( const TClau& key ){
		return (const_cast<const Map&>(*this))[key];
	}

	Map<TClau,TValor>& operator=(const Map<TClau,TValor>& m){
		m_longitud = m.m_longitud;

		for (int i = 0 ; i < m.m_longitud; i++){
			m_keys.push_back(m.m_keys[i]);
			m_values.push_back(m.m_values[i]);
		}

		return *this;
	}

private:
	int m_longitud;
	vector<TClau> m_keys;
	vector<TValor> m_values;
	TValor m_defaultValue;
	TClau m_defaultKey;

};
