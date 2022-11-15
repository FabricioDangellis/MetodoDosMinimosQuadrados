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

vector<double> XY2(vector<double> xy) {
	vector<double> xy2;
	for (int i = 0; i < xy.size(); i++) {
		xy2.push_back(pow(xy[i], 2));
	}
	return xy2;
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

vector<double> SGRegPoli(vector<double> vetX, double A, double B, double C,  double Ym) {
	vector<double> SGReg;
	for (int i = 0; i < vetX.size(); i++) {
		SGReg.push_back(pow(((A * (vetX[i] * vetX[i]) + (B * vetX[i]) + C) - Ym), 2));
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

vector<double> Pivoteamento( double x4, double x3, double x2, double x, double n, double xy2, double xy, double y) {
	vector<double> ABC;

	double m[3][4];

	m[0][0] = x4;  m[0][1] = x3;  m[0][2] = x2;  m[0][3] = xy2;
	m[1][0] = x3;  m[1][1] = x2;  m[1][2] = x;   m[1][3] = xy;
	m[2][0] = x2;  m[2][1] = x;   m[2][2] = n;   m[2][3] = y;

	double pivo, ml2, ml3;

	pivo = x4;
	ml2 = x3 / pivo;
	ml3 = x2 / pivo;

	m[1][0] -= ml2 * m[0][0];
	m[1][1] -= ml2 * m[0][1];
	m[1][2] -= ml2 * m[0][2];
	m[1][3] -= ml2 * m[0][3];

	m[2][0] -=  ml3 * m[0][0];
	m[2][1] -=  ml3 * m[0][1];
	m[2][2] -= ml3 * m[0][2];
	m[2][3] -= ml3 * m[0][3];

	pivo = m[1][1];
	ml3 = m[2][1] / pivo;

	m[2][0] -= ml3 * m[1][0];
	m[2][1] -= ml3 * m[1][1];
	m[2][2] -= ml3 * m[1][2];
	m[2][3] -= ml3 * m[1][3];

	double c = m[2][3] / m[2][2];
	double b = (m[1][3] - m[1][2] * c) / m[1][1];
	double a = ((m[0][3] - m[0][2] * c - m[0][1] * b) / m[0][0]);

	ABC.push_back(a);
	ABC.push_back(b);
	ABC.push_back(c);

	return ABC;
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
	vector<double> xy;
	vector<double> xy2;
	vector<double> x2;
	vector<double> x3;
	vector<double> x4;

	vector<double> abc;

	xy = XY(vetX, vetY);
	x2 = X2(vetX);
	x3 = X3(vetX);
	x4 = X4(vetX);
	xy2 = XY(x2, vetY);

	abc = Pivoteamento(Somatorio(x4), Somatorio(x3), Somatorio(x2), Somatorio(vetX), vetX.size(), Somatorio(xy2), Somatorio(xy), Somatorio(vetY));
	double Ym = CalculaYMedio(vetY);
	double r2 = R2(Somatorio(SGRegPoli(vetX, abc[0], abc[1], abc[2], Ym)), Somatorio(SQTot(vetY, Ym)));

	cout << endl << endl;
	cout << "================ POLINOMIAL ================\n";

	cout << Somatorio(SGRegPoli(vetX, abc[0], abc[1], abc[2], Ym));
	cout << "n= ";
	cout << vetX.size() << endl;
	cout << fixed;
	cout.precision(6);
	cout << "a= " << abc[0] << endl;
	cout << "b= " << abc[1] << endl;
	cout << "c= " << abc[2] << endl;
	cout << "Ym= " << Ym << endl;
	cout << "R^2= " << r2 << endl;
	cout << endl << endl;
}