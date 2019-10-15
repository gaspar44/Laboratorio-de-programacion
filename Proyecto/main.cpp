// comparing apples with apples
#include <iostream>
#include <string>
#include <stdio.h>
#include "MatriuDispersa.h"
using namespace std;

int main ()
{
	//MatriuDispersa m = MatriuDispersa();
	//m.resize(7, 7);
	Matriu m2 = Matriu(7,7);
	//m2.resize(3, 3);

	//int * p = new int[1];
//	p[43] = 0;
//	cout<<p[43]<<endl;
//	delete p;
//	cout<<p[43]<<endl;
//

	//m.setValor(1, 2, 1);

	for (int i = 0; i < 7 ;i++){
		for (int j = 0; j < 7 ; j++){
			float value = m2.getValor(i, j);
			cout<<value<<" , ";
		}

		cout<<endl;
	}
  return 0;
}
