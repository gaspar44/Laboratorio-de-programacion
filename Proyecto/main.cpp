// comparing apples with apples
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include "MatriuDispersa.h"
#include <cstdio>
#include <ctime>
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
//	int valueToReserve = 75887;
//	double duration;
//	std::clock_t start = std::clock();
//	MatriuDispersa m2 = MatriuDispersa(valueToReserve,valueToReserve);
//	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

//	cout<<"printf: "<< duration <<'\n';
	MatriuDispersa m = MatriuDispersa("Xarxa1.txt");

	showMatrix(m, 8);


  return 0;
}
