#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

/*=========================================FUNÇÕES DE APOIO=============================================*/

double controle;

double Somatorio(vector<double> vet) {
	double somatorio = 0;
	for (int i = 0; i < vet.size(); i++) {
		somatorio += vet[i];
	}
	return somatorio;
}

vector<double> CalculaLN(vector<double> vet) {
	vector<double> ln;

	for (int i = 0; i < vet.size(); i++) {
		ln.push_back(log(vet[i]) / log(exp(1)));
	}
	return ln;
}

vector<double> XY(vector<double> vetX, vector<double> vetY) {
	vector<double> XY;
	for (int i = 0; i < vetX.size(); i++) {
		controle = vetX[i] * vetY[i];
		XY.push_back(controle);
	}
	return XY;
}

vector<double> X2(vector<double> vet) {
	vector<double> X2;
	for (int i = 0; i < vet.size(); i++) {
		X2.push_back(pow(vet[i], 2));
	}
	return X2;
}

vector<double> X3(vector<double> vet) {
	vector<double> X3;
	for (int i = 0; i < vet.size(); i++) {
		X3.push_back(pow(vet[i], 3));
	}
	return X3;
}

vector<double> X4(vector<double> vet) {
	vector<double> X4;
	for (int i = 0; i < vet.size(); i++) {
		X4.push_back(pow(vet[i], 4));
	}
	return X4;
}

double CalculaA(double n, double somatorioXY, double somatorioX, double somatorioY, double somatorioX2) {
	double A;
	A = ((n * somatorioXY) - (somatorioX * somatorioY)) / ((n * somatorioX2) - (pow(somatorioX, 2)));
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
	for (int i = 0; i < vetX.size(); i++) {
		SGReg.push_back(pow(((A * vetX[i] + B) - Ym), 2));
	}
	return SGReg;
}

vector<double> SGRegExp(vector<double> vetX, double A, double B, double Ym) {
	vector<double> SGReg;
	for (int i = 0; i < vetX.size(); i++) {
		SGReg.push_back(pow(((B * exp(A*vetX[i])) - Ym), 2));
	}
	return SGReg;
}

vector<double> SGRegGeo(vector<double> vetX, double A, double B, double Ym) {
	vector<double> SGReg;
	for (int i = 0; i < vetX.size(); i++) {
		SGReg.push_back(pow(((B * (pow(vetX[i],A)))-Ym), 2));
	}
	return SGReg;
}

vector<double> SQTot(vector<double> vetY, double Ym) {
	vector<double> SQTot;
	for (int i = 0; i < vetY.size(); i++) {
		SQTot.push_back(pow((vetY[i] - Ym), 2));
	}
	return SQTot;
}

double R2(double somatorioSGReg, double somatorioSQTot) {
	double R2;
	R2 = somatorioSGReg / somatorioSQTot;
	return R2;
}


/*=========================================FUNÇÕES DOS METODOS=============================================*/


//Método Linear
void Linear(vector<double> vetX, vector<double> vetY) {

	vector<double> xy;
	xy = XY(vetX, vetY);
	
	double A = CalculaA(vetX.size(), Somatorio(xy), Somatorio(vetX), Somatorio(vetY), Somatorio(X2(vetX)));
	double B = CalculaB(Somatorio(vetX), Somatorio(XY(vetX, vetY)), Somatorio(vetY), Somatorio(X2(vetX)), vetX.size());
	double Ym = CalculaYMedio(vetY);
	double r2 = R2(Somatorio(SGReg(vetX, A, B, Ym)), Somatorio(SQTot(vetY, Ym)));

	cout << endl << endl;
	cout << "================ LINEAR ================\n";

	cout << "n= ";
	cout << vetX.size() << endl;
	cout << fixed;
	cout.precision(6);
	cout << "a= " << A << endl;
	cout << "b= " << B << endl;
	cout << "Ym= " << Ym << endl;
	cout << "R^2= " << r2 << endl;
	cout << endl << endl;

}

//Método Logaritimo
void Logaritimo(vector<double> vetX, vector<double> vetY) {
	vector<double> lnX;
	vector<double> xy;

	lnX = CalculaLN(vetX);
	xy = XY(lnX, vetY);
	double A = CalculaA(lnX.size(), Somatorio(xy), Somatorio(lnX), Somatorio(vetY), Somatorio(X2(lnX)));
	double B = CalculaB(Somatorio(lnX), Somatorio(xy), Somatorio(vetY), Somatorio(X2(lnX)), lnX.size());
	double Ym = CalculaYMedio(vetY);
	double r2 = R2(Somatorio(SGReg(lnX, A, B, Ym)), Somatorio(SQTot(vetY, Ym)));

	cout << endl << endl;
	cout << "================ LOGARITIMO ================\n";

	cout << "n= ";
	cout << vetX.size() << endl;
	cout << fixed;
	cout.precision(6);
	cout << "a= " << A << endl;
	cout << "b= " << B << endl;
	cout << "Ym= " << Ym << endl;
	cout << "R^2= " << r2 << endl;
	cout << endl << endl;
}

//Método Geometrico
void Geometrico(vector<double> vetX, vector<double> vetY) {
	vector<double> lnX;
	vector<double> lnY;
	vector<double> xy;

	lnX = CalculaLN(vetX);
	lnY = CalculaLN(vetY);
	xy = XY(lnX, lnY);
	double A = CalculaA(lnX.size(), Somatorio(xy), Somatorio(lnX), Somatorio(lnY), Somatorio(X2(lnX)));
	double B = CalculaB(Somatorio(lnX), Somatorio(xy), Somatorio(lnY), Somatorio(X2(lnX)), lnY.size());
	B = exp(B);
	double Ym = CalculaYMedio(vetY);
	double r2 = R2(Somatorio(SGRegGeo(vetX, A, B, Ym)), Somatorio(SQTot(vetY, Ym)));

	cout << endl << endl;
	cout << "================ GEOMETRICO ================\n";

	cout << "n= ";
	cout << vetX.size() << endl;
	cout << fixed;
	cout.precision(6);
	cout << "a= " << A << endl;
	cout << "b= " << B << endl;
	cout << "Ym= " << Ym << endl;
	cout << "R^2= " << r2 << endl;
	cout << endl << endl;
}

//Metodo Exponêncial
void Exponencial(vector<double> vetX, vector<double> vetY) {
	vector<double> lnY;
	vector<double> xy;

	lnY = CalculaLN(vetY);
	xy = XY(vetX, lnY);
	double A = CalculaA(vetX.size(), Somatorio(xy), Somatorio(vetX), Somatorio(lnY), Somatorio(X2(vetX)));
	double B = CalculaB(Somatorio(vetX), Somatorio(xy), Somatorio(lnY), Somatorio(X2(vetX)), lnY.size());
	B = exp(B);
	double Ym = CalculaYMedio(vetY);
	double r2 = R2(Somatorio(SGRegExp(vetX, A, B, Ym)), Somatorio(SQTot(vetY, Ym)));

	cout << endl << endl;
	cout << "================ EXPONENCIAL ================\n";

	cout << "n= ";
	cout << vetX.size() << endl;
	cout << fixed;
	cout.precision(6);
	cout << "a= " << A << endl;
	cout << "b= " << B << endl;
	cout << "Ym= " << Ym << endl;
	cout << "R^2= " << r2 << endl;
	cout << endl << endl;
}

//Método Polinomial
void Polinomial(vector<double> vetX, vector<double> vetY) {

}