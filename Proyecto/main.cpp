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
	int valueToReserve = 5;
	int valueToeduce = 12;

	//MatriuDispersa m = MatriuDispersa();
	//m.resize(7, 7);
	SimmetricMatrix m2 = SimmetricMatrix(valueToReserve,valueToReserve);
	m2.setValor(1, 2, 5);
	m2.resize(valueToeduce, valueToeduce);
	showMatrix(m2, valueToeduce);

	//m2.setValor(10, 2, 1);




  return 0;
}
