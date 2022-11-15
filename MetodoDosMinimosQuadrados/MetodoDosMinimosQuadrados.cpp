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
	do {
		cout << "Qual tipo de metodo você quer? \n";
		cout << "(1) Linear \n(2) Logaritima \n(3) Geometrica \n(4) Exponencial \n(5) Polinomial \n(6) Sair\n";
		cin >> resposta;

		switch (resposta)
		{
		case 1:
			Linear(vetX, vetY);
			break;
		case 2:
			Logaritimo(vetX, vetY);
			break;
		case 3:
			Geometrico(vetX, vetY);
			break;
		case 4:
			Exponencial(vetX, vetY);
			break;
		case 5:
			Polinomial(vetX, vetY);
			break;
		case 6:
			return 0;
		default:
			break;
		}
	}while(resposta != 6);
}