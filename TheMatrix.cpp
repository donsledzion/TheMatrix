#include <conio.h>      // obsługa _getch()
#include "Matrix.h"     // nagłówek z deklaracją obiektu klasy Matrix, w tym jego metod

int main()
{
	Matrix macierz;	            	                // utworzenie obiektu typu Matrix

	macierz.read();		                            // wywołanie na utworzonym obiekcie metody wczytywania elementów macierzy

	macierz.showRes();	                            // wywołanie metody wyświetlającej wyniki na ekranie

	int znak;
	while (znak = _getch())                         // pętla pobiera znak ze strumienia wejścia
	{
		if ((znak == 81) || (znak == 113)) break;   // wyjście z pętli jeśli wczyany znak to "q" lub "Q"

		else if (znak == 43) macierz.precINC();     // jeśli wczytany znak to "+" (plus) to następuje wywołanie metody zwiększającej precyzję wyświetlanych wyników

		else if (znak == 45) macierz.precDEC();     // jeśli wczytany znak to "-" (minus) to następuje wywołanie metody zmniejszającej precyzję wyświetlanych wyników
	}

}
