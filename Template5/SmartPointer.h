#pragma once
#include <iostream>
using namespace std;

template <class T>
class SmartPointer
{
public:
	SmartPointer() : m_originalPointer(nullptr) {};
	SmartPointer<T>(T* &pointerToCast) {

		m_originalPointer = pointerToCast;
		pointerToCast = nullptr;

	}

	SmartPointer<T> operator=(T* &pointerToCast){
		if (m_originalPointer != nullptr){
			delete pointerToCast;
		}

		m_originalPointer = pointerToCast;
		pointerToCast = nullptr;

		return *this;
	}

	bool getInfo() { return m_originalPointer == nullptr ;}
private:
	T* m_originalPointer;
};

