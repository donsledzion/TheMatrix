#include <iostream>
#include <iomanip>
#include "Matrix.h"
#include "functions.h"

//===============================================================================================================================================================
//                                  KONSTRUKTOR DLA OBIEKTU KLASY Matrix
//===============================================================================================================================================================
Matrix::Matrix(double a, bool s, short p, short minP, short maxP)
{
	for (int i = 0 ; i <4 ; i++)
		for (int j = 0; j < 4; j++)
		{
			A[i][j] = a;
			status[i][j] = s;
		}
	precision	= p;
	minPrec = minP;                     // ustalenie wartości minimalnej i maksymalnej precyzji jako parametrów
	maxPrec = maxP;                     // inicjowanych w konstruktorze obiektu klasy Matrix
}
//===============================================================================================================================================================
//                      METODA WCZYTUJĄCA MACIERZ A
//===============================================================================================================================================================
void Matrix::read()						//metoda wczytuje elementy tablicy sprawdzając poprawność wprowadzonych danych
{
	system("cls");                      //wyczyszczenie ekranu przed rozpoczęciem wczytywania elementów
	for (int i = 0; i < 4; i++)         //wywołanie pętli przechodzącej przez kolejne elementy macierzy
	{
		for (int j = 0; j < 4; j++)
		{
                                                    // dla każdego wczytywanego elementu:
			greetings();                            // wyświetlenie komunikatu nagłówkowego,
			printf("\tA[%d][%d]=\n\n",i+1,j+1);     // wyświetlenie informacji o wczytywanym elemencie (współrzędne w macierzy)
			showA();                                // wyświetlenie aktualnego stanu macierzy,
			printf("\033[8;17f");                   // przesunięcie kursora na pozycję [8,17], gdzie ma być podana wartość kolejnego elementu
			A[i][j] = readElement();                // przypisanie do elementu A[i][j] wartości zwróconej przez funkcję wczytywania elementu
			status[i][j] = true;                    // po wczytaniu elementu przypisanie do tablicy "statusów" macierzy A informacji o tym, że element został wczytany
			system("cls");                          // wyczyszczenie ekranu
		}
	}
}

//===============================================================================================================================================================
//                      METODA "RYSUJĄCA" MACIEZ NA EKRANIE
//===============================================================================================================================================================
void Matrix::showA()
{
	//===============================================================================================
	// Aby prawidłowo wyświetlać macierz należy wyznaczyć długość najdłuższej liczby
	// w każdej kolumnie
	//===============================================================================================

	// tablica na wartości początkowe długości liczb do wyświetlenia
	int width[4] = { 2 + precision,2 + precision,2 + precision,2 + precision };
	//===============================================================================================

	// Pętla przeszukuje tablicę kolumnami w poszukiwaniu najdłuższych liczb
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (countTotal(A[j][i],precision) > width[i]) width[i] = countTotal(A[j][i],precision);
			}
		}
	//===============================================================================================
		int rW = 0;                                             // rW (od rowWidth) - zmienna na szerokość całkowitą wiersza

		printf("\t\tMACIERZ A:\n\n");                           // etykieta macierzy

		for (int j = 0; j < 4; j++)                             // pętla wykonuje się 4 krotnie, "rysując" kolejne wiersze macierzy
		{                                                       // w każdej iteracji:
			rW = printRow(precision, width, A[j], status[j]);   // 1. wywołanie funkcji rysującej wiersz z jednoczesnym zapisaniem w zmiennej rW wartości zwracanej przez tą funkcję - szerokości całkowitej wiersza
			printf("\t|");                                      // 2. "otwarcie" pustego wiersza odseparowującego kolejne wiersze z danymi
			for (int i = 0; i < rW; i++) printf(" ");           // 3. wypisywanie "spacji" tak długo aby wypełnić całą szerokość wiersza (wg wartości zwróconej przez funkcję printRow)
			printf("|\n");                                      // 4. "zamknięcie" pustego wiersza.

		}
}
//===============================================================================================================================================================
//                  METODA "RYSUJĄCA" MACIERZ ODWROTNĄ NA EKRANIE
//===============================================================================================================================================================
void Matrix::showInvA() // metoda wyświetlająca maciez odwrotną do macierzy A (InvA) na ekranie
{

						//------------------------------------------------------------------------------------------------------//
						// wywołanie metody calcInvA(), która:																	//
						// a) oblicza wartość wyznacznika macierzy A															//
	calcInvA();			// b) dla niezerowego wyznacznika oblicza wartości elementów macierzy dopełnień algebraicznych			//
						//    a następnie wymnaża je przez odwrotność wyznacznika obliczając macierz odwrotną do macierzy A		//
						//------------------------------------------------------------------------------------------------------//
	if (detA != 0)		// dla wyznacznika niezerowego następuje wyświetlenie uprzednio wyliczonej macierzy odwrotnej			//
	{
		int width[4] = { 2 + precision,2 + precision,2 + precision,2 + precision };

		// tablica na wartości początkowe długości liczb do wyświetlenia (powyżej)
		//
		//===============================================================================================
		int tmpWidht = 0;	// zmienna na podręczne przechowywanie długości aktualnie rozpatrywanej liczby


		// Pętla przeszukuje tablicę kolumnami w poszukiwaniu najdłuższych liczb
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (countTotal(invA[j][i],precision) > width[i]) width[i] = countTotal(invA[j][i],precision);
			}
		}
		//===============================================================================================
		// PONIŻEJ WYŚWIETLANIE ANALOGICZNE JAK DLA MACIERZY PODSTAWOWEJ
		//===============================================================================================
		int rW = 0;

		printf("\tMACIERZ ODWROTNA DO A:\n\n");

		for (int j = 0; j < 4; j++)
		{
			rW = printRow(precision, width, invA[j], status[j]);
			printf("\t|");
			for (int i = 0; i < rW; i++) printf(" ");
			printf("|\n");

		}
	}
	else
	{
    // dla zerowego wyznacznika wyświetlenie komunikatu o braku macierzy odwrtonej
		printf("________________________________________\n");
		printf("|\t\t\t\t\t|\n");
		printf("|\t     WYZNACZNIK = 0\t     \t|\n");
		printf("|_______________________________________|\n");
		printf("|\t\t\t\t\t|\n");
		printf("|\t   MACIERZ OSOBLIWA\t        |\n");
		printf("|   NIE POSIADA MACIERZY ODWROTNEJ   \t|\n");
		printf("|_______________________________________|\n");

	}
}

//===============================================================================================================================================================
//                  METODA OBLICZAJĄCA WYZNACZNIK MACIERZY (ZE STAŁEGO WZROU)
//===============================================================================================================================================================
long double Matrix::calcDet() // metoda obliczająca wartość wyznacznika macierzy A  ze stałego wzoru:
{
	detA = 	A[0][0] * A[1][1] * A[2][2] * A[3][3] + A[0][0] * A[1][2] * A[2][3] * A[3][1] + A[0][0] * A[1][3] * A[2][1] * A[3][2] +
			A[0][1] * A[1][0] * A[2][3] * A[3][2] + A[0][1] * A[1][2] * A[2][0] * A[3][3] + A[0][1] * A[1][3] * A[2][2] * A[3][0] +
			A[0][2] * A[1][0] * A[2][1] * A[3][3] + A[0][2] * A[1][1] * A[2][3] * A[3][0] + A[0][2] * A[1][3] * A[2][0] * A[3][1] +
			A[0][3] * A[1][0] * A[2][2] * A[3][1] + A[0][3] * A[1][1] * A[2][0] * A[3][2] + A[0][3] * A[1][2] * A[2][1] * A[3][0] -

			A[0][0] * A[1][1] * A[2][3] * A[3][2] - A[0][0] * A[1][2] * A[2][1] * A[3][3] - A[0][0] * A[1][3] * A[2][2] * A[3][1] -
			A[0][1] * A[1][0] * A[2][2] * A[3][3] - A[0][1] * A[1][2] * A[2][3] * A[3][0] - A[0][1] * A[1][3] * A[2][0] * A[3][2] -
			A[0][2] * A[1][0] * A[2][3] * A[3][1] - A[0][2] * A[1][1] * A[2][0] * A[3][3] - A[0][2] * A[1][3] * A[2][1] * A[3][0] -
			A[0][3] * A[1][0] * A[2][1] * A[3][2] - A[0][3] * A[1][1] * A[2][2] * A[3][0] - A[0][3] * A[1][2] * A[2][0] * A[3][1];
	return detA;	//zwrócenie przez funkcję wartości wyznacznika macierzy A
}
//===============================================================================================================================================================
//                  METODA WYŚWIETLAJĄCA TABELKĘ Z WARTOŚCIĄ WYZNACZNIKA MACIERZY
//===============================================================================================================================================================
void Matrix::showDet(long double d)
{
	unsigned int detLength = countTotal(d, precision);
	std::cout << std::setprecision(precision) << std::fixed;
	//--------------------------------------------------------
	printf("\t ");
	for (int i = 0; i < 30 + detLength; i++) printf("_");
	printf("\n");
	//--------------------------------------------------------
	printf("\t|");
		for (int i = 0; i < 30 + detLength; i++) printf(" ");
	printf("|\n");
	//--------------------------------------------------------
	printf("\t|\tWYZNACZNIK = ");
	std::cout << d;
	for (int i = 0; i < 10 ; i++) printf(" ");
	printf("|\n");
	//--------------------------------------------------------
	//--------------------------------------------------------
	printf("\t|");
	for (int i = 0; i < 30 + detLength; i++) printf("_");
	printf("|\n");
	//--------------------------------------------------------
}
//===============================================================================================================================================================
//                  METODA OBLICZAJĄCA MACIERZ DOPEŁNIEŃ ALGEBRAICZNYCH MACIERZY A (NIEZBĘDNEJ DO OBLICZENIA MACIERZY ODWROTNEJ)
//===============================================================================================================================================================
void Matrix::calcB() //metoda obliczająca macierz dopełnień algebraicznych macierzy A
{
	//wartości elementów macierzy dopełnień algebraicznych "B" obliczane są ze stałego wzoru na podstawie wartości macierzy wejściowej "A"
	B[0][0] = A[1][1] * A[2][2] * A[3][3] + A[1][2] * A[2][3] * A[3][1] + A[1][3] * A[2][1] * A[3][2] - A[1][1] * A[2][3] * A[3][2] - A[1][2] * A[2][1] * A[3][3] - A[1][3] * A[2][2] * A[3][1];

	B[0][1] = A[0][1] * A[2][3] * A[3][2] + A[0][2] * A[2][1] * A[3][3] + A[0][3] * A[2][2] * A[3][1] - A[0][1] * A[2][2] * A[3][3] - A[0][2] * A[2][3] * A[3][1] - A[0][3] * A[2][1] * A[3][2];

	B[0][2] = A[0][1] * A[1][2] * A[3][3] + A[0][2] * A[1][3] * A[3][1] + A[0][3] * A[1][1] * A[3][2] - A[0][1] * A[1][3] * A[3][2] - A[0][2] * A[1][1] * A[3][3] - A[0][3] * A[1][2] * A[3][1];

	B[0][3] = A[0][1] * A[1][3] * A[2][2] + A[0][2] * A[1][1] * A[2][3] + A[0][3] * A[1][2] * A[2][1] - A[0][1] * A[1][2] * A[2][3] - A[0][2] * A[1][3] * A[2][1] - A[0][3] * A[1][1] * A[2][2];

	B[1][0] = A[1][0] * A[2][3] * A[3][2] + A[1][2] * A[2][0] * A[3][3] + A[1][3] * A[2][2] * A[3][0] - A[1][0] * A[2][2] * A[3][3] - A[1][2] * A[2][3] * A[3][0] - A[1][3] * A[2][0] * A[3][2];

	B[1][1] = A[0][0] * A[2][2] * A[3][3] + A[0][2] * A[2][3] * A[3][0] + A[0][3] * A[2][0] * A[3][2] - A[0][0] * A[2][3] * A[3][2] - A[0][2] * A[2][0] * A[3][3] - A[0][3] * A[2][2] * A[3][0];

	B[1][2] = A[0][0] * A[1][3] * A[3][2] + A[0][2] * A[1][0] * A[3][3] + A[0][3] * A[1][2] * A[3][0] - A[0][0] * A[1][2] * A[3][3] - A[0][2] * A[1][3] * A[3][0] - A[0][3] * A[1][0] * A[3][2];

	B[1][3] = A[0][0] * A[1][2] * A[2][3] + A[0][2] * A[1][3] * A[2][0] + A[0][3] * A[1][0] * A[2][2] - A[0][0] * A[1][3] * A[2][2] - A[0][2] * A[1][0] * A[2][3] - A[0][3] * A[1][2] * A[2][0];

	B[2][0] = A[1][0] * A[2][1] * A[3][3] + A[1][1] * A[2][3] * A[3][0] + A[1][3] * A[2][0] * A[3][1] - A[1][0] * A[2][3] * A[3][1] - A[1][1] * A[2][0] * A[3][3] - A[1][3] * A[2][1] * A[3][0];

	B[2][1] = A[0][0] * A[2][3] * A[3][1] + A[0][1] * A[2][0] * A[3][3] + A[0][3] * A[2][1] * A[3][0] - A[0][0] * A[2][1] * A[3][3] - A[0][1] * A[2][3] * A[3][0] - A[0][3] * A[2][0] * A[3][1];

	B[2][2] = A[0][0] * A[1][1] * A[3][3] + A[0][1] * A[1][3] * A[3][0] + A[0][3] * A[1][0] * A[3][1] - A[0][0] * A[1][3] * A[3][1] - A[0][1] * A[1][0] * A[3][3] - A[0][3] * A[1][1] * A[3][0];

	B[2][3] = A[0][0] * A[1][3] * A[2][1] + A[0][1] * A[1][0] * A[2][3] + A[0][3] * A[1][1] * A[2][0] - A[0][0] * A[1][1] * A[2][3] - A[0][1] * A[1][3] * A[2][0] - A[0][3] * A[1][0] * A[2][1];

	B[3][0] = A[1][0] * A[2][2] * A[3][1] + A[1][1] * A[2][0] * A[3][2] + A[1][2] * A[2][1] * A[3][0] - A[1][0] * A[2][1] * A[3][2] - A[1][1] * A[2][2] * A[3][0] - A[1][2] * A[2][0] * A[3][1];

	B[3][1] = A[0][0] * A[2][1] * A[3][2] + A[0][1] * A[2][2] * A[3][0] + A[0][2] * A[2][0] * A[3][1] - A[0][0] * A[2][2] * A[3][1] - A[0][1] * A[2][0] * A[3][2] - A[0][2] * A[2][1] * A[3][0];

	B[3][2] = A[0][0] * A[1][2] * A[3][1] + A[0][1] * A[1][0] * A[3][2] + A[0][2] * A[1][1] * A[3][0] - A[0][0] * A[1][1] * A[3][2] - A[0][1] * A[1][2] * A[3][0] - A[0][2] * A[1][0] * A[3][1];

	B[3][3] = A[0][0] * A[1][1] * A[2][2] + A[0][1] * A[1][2] * A[2][0] + A[0][2] * A[1][0] * A[2][1] - A[0][0] * A[1][2] * A[2][1] - A[0][1] * A[1][0] * A[2][2] - A[0][2] * A[1][1] * A[2][0];
}
//===============================================================================================================================================================
//                  METODA OBLICZAJĄCA MACIERZ ODWRTONĄ DO MACIERZY "A"
//===============================================================================================================================================================
void Matrix::calcInvA() //metoda obliczająca macierz odwrotną do macierzy A -> A^-1
{
	long double det = Matrix::calcDet();		//	wywołanie funkcji calcDet() na potrzeby obliczenia wartości wyznacznika
	if (det != 0)						//	i zapisanie wartoœci zwracanej przez tę funkcję do zmiennej "det"
	{

		//----------------------------------------------------------------------------------------- //
		//   dla niezerowego wyliczenie wartości elementów macierzy odwrotnej poprzez				//
		//    a) wywołanie funkcji calcB(), która oblicza wartości elementów macierzy "B" dopełnień	//
		//		 algebraicznych macierzy "A";														//
		//    b) przemnożenie współczynników macierzy dopełnień algebraicznych przez odwrotność		//
		//       wyznacznika macierzy "A"															//
		//----------------------------------------------------------------------------------------- //
		calcB();			// a) obliczenie elementów macierzy dopełnień algebraicznych
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				invA[i][j] = B[i][j] * ((long double)1 / det); // b) przemnożenie współczynników macierzy B przez odwrotność wyznacznika macierzy A
	}
}
//===============================================================================================================================================================
//                  METODA WYŚWIETLAJĄCA NA EKRANIE WYNIKI Z UWZGLĘDNIENIEM PRZYJĘTEJ PRECYZJI WYŚWIETLANIA
//===============================================================================================================================================================
void Matrix::showRes()
{
	system("cls");                  // wyczyszczenie ekranu przed prezentacją wyników
	greetings();                    // wypisanie komunikatu nagłówkowego programu

	printf("\n\n");

	showA();                        // wyświetlenie macierzy podstawowej A

	printf("\n\n\n");

	double det = calcDet();         // obliczenie wyznacznika

	if (det)	showDet(det);       // jeśli wyznacznik jest niezerowy to wywołanie metody wyświetlającej tabelkę z wyznacznikiem
	printf("\n\n\n");
	showInvA();                     // następnie wywołanie metody "rysującej" na ekranie macierz odwrotną (bądź komunikat o braku macierzy odwrotnej w przypadku wyznacznika zerowego
    //==========================================================================================================================================================
	if ((precision > minPrec) && (precision < maxPrec))                                             //
		printf("\nNacisnij \"+\" \\ \"-\" aby zwiekszyc \\ zmniejszyc precyzje wyswietlania\n");    // wyświetlenie ponizej wyników instrukcji o możliwości
	else if (precision <= minPrec)                                                                  // zwiększeniu lub zmniejszeniu precyzji, w zależności
		printf("\nOsiagnieto minimalna precyzje wyswietlania, nacisnij  \"+\" aby zwiekszyc\n");    // od jej aktualnej wartości
	else if (precision >=maxPrec)                                                                   //
		printf("\nOsiagnieto maksymalna precyzje wyswietlania, nacisnij  \"-\" aby zmniejszyc\n");  //
	printf("Nacisnij <q> aby zakonczyc program\n");                                                 // lub o możliwości zamknięcia programu wciśnięciem klawisza "q"
	//==========================================================================================================================================================
}

//===============================================================================================================================================================
//                  METODA ZWIĘKSZAJĄCA WARTOŚĆ PRECYZJI WYŚWIETLANYCH WYNIKÓW
//===============================================================================================================================================================
void Matrix::precINC()
{
	if (precision < maxPrec)    // jeśli aktualna wartość precyzji jest mniejsza niż dopuszczalna maksymalna:
	{
		precision++;            // to funkcja zwiększa jej wartosć...
		showRes();              // ...i wyświetla wyniki przy zwiększonej precyzji
	}
}

//===============================================================================================================================================================
//                  METODA ZMNIEJSZAJĄCA WARTOŚĆ PRECYZJI WYŚWIETLANYCH WYNIKÓW
//===============================================================================================================================================================
void Matrix::precDEC()
{
	if (precision > minPrec)    // jeśli aktualna wartość precyzji jest większa niż dopuszczalna minimalna:
	{
		precision--;            // to funkcja zmnięjsza jej wartosć...
		showRes();              // ...i wyświetla wyniki przy zmniejszonej precyzji
	}
}
//===============================================================================================================================================================
//===============================================================================================================================================================
