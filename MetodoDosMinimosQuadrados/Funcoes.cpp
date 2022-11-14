#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

/*=========================================FUNÇÕES DE APOIO=============================================*/

double Somatorio(vector<double> vet) {
	double somatorio = 0;
	for (int i = 0; i <= vet.size(); i++) {
		somatorio += vet[i];
	}
	return somatorio;
}

vector<double> XY(vector<double> vetX, vector<double> vetY) {
	vector<double> XY;
	for (int i = 0; i <= vetX.size(); i++) {
		XY.push_back(vetX[i] * vetY[i]);
	}
	return XY;
}

vector<double> X2(vector<double> vet) {
	vector<double> X2;
	for (int i = 0; i <= vet.size(); i++) {
		X2.push_back(pow(vet[i], 2));
	}
	return X2;
}

vector<double> X3(vector<double> vet) {
	vector<double> X3;
	for (int i = 0; i <= vet.size(); i++) {
		X3.push_back(pow(vet[i], 3));
	}
	return X3;
}

vector<double> X4(vector<double> vet) {
	vector<double> X4;
	for (int i = 0; i <= vet.size(); i++) {
		X4.push_back(pow(vet[i], 4));
	}
	return X4;
}

double CalculaA(double n, double somatorioXY, double somatorioX, double somatorioY, double somatorioX2) {
	double A;
	A = ((n * somatorioXY) - (somatorioX * somatorioY)) / ((n - somatorioX2) - (pow(somatorioX, 2)));
	return A;
}

double CalculaB(double somatorioX, double somatorioXY,  double somatorioY, double somatorioX2, double n) {
	double B;
	B = ((somatorioX * somatorioXY) - (somatorioY * somatorioX2)) / (pow(somatorioX, 2) - (n * somatorioX2));
	return B;
}

double CalculaYMedio(vector<double> vetY) {
	double Ym;
	Ym = Somatorio(vetY) / vetY.size();
	return Ym;
}


vector<double> SGReg(vector<double> vetX, double A, double B, double Ym) {
	vector<double> SGReg;
	for (int i = 0; i <= vetX.size(); i++) {
		SGReg.push_back(pow(((A * vetX[i] + B) - Ym), 2));
	}
	return SGReg;
}

vector<double> SQTot(vector<double> vetY, double Ym) {
	vector<double> SQTot;
	for (int i = 0; i <= vetY.size(); i++) {
		SQTot.push_back(pow((vetY[i] - Ym), 2));
	}
	return SQTot;
}


/*=========================================FUNÇÕES DOS METODOS=============================================*/


//Método Linear
void Linear(vector<double> vetX, vector<double> vetY) {
	
	double A = CalculaA(vetX.size(), Somatorio(XY(vetX, vetY)), Somatorio(vetX), Somatorio(vetY), Somatorio(X2(vetX)));
	double B = CalculaB(Somatorio(vetX), Somatorio(XY(vetX, vetY)), Somatorio(vetY), Somatorio(X2(vetX)), vetX.size());



}

//Método Logaritimo
void Logaritimo(vector<double> vetX, vector<double> vetY) {

}

//Método Geometrico
void Geometrico(vector<double> vetX, vector<double> vetY) {

}

//Metodo Exponêncial
void Exponencial(vector<double> vetX, vector<double> vetY) {

}

//Método Polinomial
void Polinomial(vector<double> vetX, vector<double> vetY) {

}