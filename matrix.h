#pragma once

using namespace std;

class Matrix
{

private:

	long double A[4][4];								//zmienna przechowująca macierz podstawową A

	long double detA;									//zmienna przechowująca wartość wyznacznika macierzy A

	double B[4][4];										//zmienna przechowująca macierz dopełnień algebraicznych macierzy A -> macierz B

	long double invA[4][4];								//zmienna przechowująca macierz odwrotną do macierzy A

	bool status[4][4];									// zmienna przechowująca informacje o tym czy dany element został wczytany

	short precision;									// parametr definiujący dokładność wyświetlania liczb ułamkowych. Liczba miejsc po przecinku dziesiętnym

	short minPrec;										// parametr definiujący minimalną precyzję wyświetlania

	short maxPrec;										// parametr definiujący maksymalną precyzję wyświetlania

public:

	Matrix(double a=0, bool s=false, short p=2, short minP=1, short maxP=18);		// Konstruktor obiektu klasy Matrix

	void read();										//metoda wczytująca do zmiennej A elementy tej macierzy

	void showA();										//metoda wyświetlająca maciez A na ekranie

	void showInvA();					            	//metoda wyświetlająca maciez odwrotną do macierzy A (InvA) na ekranie

	long double calcDet();					        	//metoda obliczająca wartoœæ wyznacznika macierzy A

	void showDet(long double);				           	//metoda wyświetlająca w sformatowany sposób wartość wyznacznika macierzy A

	void calcB();							            //metoda obliczająca macierz dopełnień algebraicznych macierzy A

	void calcInvA();						            //metoda obliczająca macierz odwrotną do macierzy A -> A^-1

	void showRes();                                     //metoda odpowiedzialna za kompleksowe wyświetlenie wyników na ekranie

	void precINC();                                     //metoda zwiększająca precyzję wyświetlania wyników

	void precDEC();                                     //metoda zmniejszająca precyzję wyświetlania wyników

};

