#pragma once
#include <stdlib.h>
#include <iostream>
#include <utility>
#include "TreeRB.hpp"
using namespace std;



template<class TClau, class TValor>
class PairMap
{
public:
	TClau first;
	TValor second;
	PairMap() { first = TClau(); second = TValor(); }
	PairMap(TClau primer, TValor segon) { first = primer; second = segon; }
	bool operator<(PairMap<TClau, TValor> valor) const { return (first < valor.first); }
	bool operator==(PairMap<TClau, TValor> valor) const {	return (first == valor.first); }
	friend ostream& operator<<(ostream& out, PairMap<TClau, TValor> valor)
	{
		out << "<" << valor.first << ", " << valor.second << ">";
		return out;
	}
};



template<class TClau, class TValor>
class Map
{
public:
	Map();
	Map(const Map<TClau, TValor>& m);
	~Map(){};
	bool esBuit() const;
	TValor& operator[](const TClau& clau);
	void afegeix(const TClau& clau, const TValor& valor);

	friend std::ostream& operator<<(std::ostream& out, const Map<TClau, TValor>& m){
		out<<m.m_keyMap;
		return out;
	}
private:
	TreeRB<PairMap<TClau,TValor>> m_keyMap;

};

template<class TClau, class TValor>
Map<TClau,TValor>::Map(){
	m_keyMap = TreeRB<PairMap<TClau,TValor>>();
}

template<class TClau, class TValor>
Map<TClau,TValor>::Map(const Map<TClau,TValor>& m){

	m_keyMap = m.m_keyMap;
}

template<class TClau, class TValor>
bool Map<TClau,TValor>::esBuit() const{
	return m_keyMap.isEmpty();
}

template<class TClau, class TValor>
TValor& Map<TClau,TValor>::operator[](const TClau& key){
	TValor emptyValor = TValor();
	PairMap<TClau,TValor> pairToSearch = PairMap<TClau,TValor>(key,emptyValor);
	TreeRB<PairMap<TClau,TValor>> *ret = new TreeRB<PairMap<TClau,TValor>>();
	m_keyMap.cerca(pairToSearch, ret);
	return ret->getData().second;
}

template<class TClau, class TValor>
void Map<TClau,TValor>::afegeix(const TClau& key,const TValor & value){
	PairMap<TClau,TValor> pairToInsert = PairMap<TClau,TValor>(key,value);
	m_keyMap.insert(pairToInsert);
}
