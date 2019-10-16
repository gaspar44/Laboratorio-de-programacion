// comparing apples with apples
#include <iostream>
#include <string>
#include <stdio.h>
#include "MatriuDispersa.h"
using namespace std;

void showMatrix(SimmetricMatrix m, int memory){
	float value;
	for (int i = 0; i < memory ;i++){
		for (int j = 0; j < memory ; j++){
			 m.getValor(i, j,value);
			cout<<value<<" , ";
		}

		cout<<endl;
	}
}

int main ()
{
	int valueToReserve = 20;
	int valueToeduce = 25;

	//MatriuDispersa m = MatriuDispersa();
	//m.resize(7, 7);
	MatriuDispersa m2 = MatriuDispersa(valueToReserve,valueToReserve);
	//m2.init(valueToReserve,valueToReserve);
	m2.setValor(4, 5, 5);
	float temp;
	m2.getValor(4, 5, temp);
	cout<<temp<<endl;
	//MatriuDispersa m = MatriuDispersa(m2);
	m2.resize(valueToeduce, valueToeduce);
	showMatrix(m2, valueToReserve);
	cout<<temp<<endl;

	//m2.setValor(10, 2, 1);




  return 0;
}
