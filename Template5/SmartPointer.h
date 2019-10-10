#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class SmartPointer
{
public:
	SmartPointer() : m_originalPointer(nullptr)  {};
	SmartPointer<T>(T* &pointerToCast) {
		bool isDeleteNeeded = false;
		if (m_originalPointer != nullptr){
			isDeleteNeeded = true;
		}

		m_originalPointer = new T;
		*m_originalPointer = *pointerToCast;

		if(isDeleteNeeded){
			delete pointerToCast;
		}

	}

	SmartPointer<T>(T* pointerToCast) {
		bool isDeleteNeeded = false;
		if (m_originalPointer != nullptr){
			isDeleteNeeded = true;
		}

		m_originalPointer = new T;
		*m_originalPointer = *pointerToCast;

		if(isDeleteNeeded){
			delete pointerToCast;
		}

	}


	SmartPointer<T> operator=(T* &pointerToCast){

		bool isDeleteNeeded = false;
		if (m_originalPointer != nullptr){
			isDeleteNeeded = true;
		}

		m_originalPointer = new T;
		*m_originalPointer = *pointerToCast;

		if(isDeleteNeeded){
			delete pointerToCast;
		}

		return *this;
	}

	SmartPointer<T> operator =(SmartPointer<T> spToAsign){
		m_originalPointer = new T;
		m_originalPointer = spToAsign.m_originalPointer;

		spToAsign.m_originalPointer = nullptr;

		return *this;

	}

	T &operator *() {
		return *m_originalPointer;
	}

	T * operator ->() {
		return m_originalPointer;
	}

//	void* operator new(size_t const size){
//		void *voidPointer =  malloc(size);
//		return voidPointer;
//	}


	bool isNull() { return m_originalPointer == nullptr ;}
private:
	T* m_originalPointer;
};

