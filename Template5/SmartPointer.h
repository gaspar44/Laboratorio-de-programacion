#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class SmartPointer
{
public:
	SmartPointer() : m_originalPointer(nullptr)  {};
	~SmartPointer() {
		releaseMemory();
	}

	SmartPointer<T>(T* pointerToCast) {
		cout<<"SmartPointer<T>(T* pointerToCast)"<<endl;
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

	SmartPointer<T>(const SmartPointer<T> &spToAsign){
		cout<<"SmartPointer<T>(SmartPointer<T> spToAsign)"<<endl;

		m_originalPointer = new T;
		*m_originalPointer = *spToAsign.m_originalPointer;
//		delete spToAsign.m_originalPointer;
//		spToAsign.m_originalPointer = nullptr;

	}


	SmartPointer<T> operator=(T* &pointerToCast){
		cout<<"operador=(T* &pointerToCast"<<endl;

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
		cout<<"operator =(SmartPointer<T> spToAsign)"<<endl;

		m_originalPointer = new T;
		T *temp = spToAsign.m_originalPointer;

		*m_originalPointer = *temp;

		delete temp;
		spToAsign.m_originalPointer = nullptr;

		return *this;

	}

	T &operator *() {
		return *m_originalPointer;
	}

	T * operator ->() {
		return m_originalPointer;
	}


	bool isNull() { return m_originalPointer == nullptr ;}
private:
	T* m_originalPointer;

	void releaseMemory() {
		delete m_originalPointer;
		m_originalPointer = nullptr;
	}
};

