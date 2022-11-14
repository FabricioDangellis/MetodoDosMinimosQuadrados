#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include "Funcoes.h"

using std::ifstream;
using namespace std;

int main() {
    double Y;
	double X;
    vector<double> vetX;
	vector<double> vetY;

	ifstream fin;
	fin.open("Base.txt");

    while (!fin.eof())
    {
		fin >> X;
		fin >> Y;

		vetX.push_back(X);
		vetY.push_back(Y);
    }

    fin.close();

	int resposta;
	cout << "Qual tipo de metodo você quer? \n";
	cout << "1) Linear \n2)Logaritima \n3)Geometrica \n4)Exponencial \n5)Polinomial \n6)Sair\n";
	cin >> resposta;

	switch (resposta)
	{
	case 1: 
		Linear(vetX, vetY);

	case 2:
		//Logaritima();

	case 3:
		//Geometrica();

	case 4:
		//Exponencial();

	case 5:
		//Polinomial();

	case 6:
		
	default:
		break;
	}

	return 0;
}