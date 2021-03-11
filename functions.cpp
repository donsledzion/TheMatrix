#pragma once
#include <iostream>
#include "functions.h"
#include <string>
#include <iomanip>

//==================================================================================================================================================
void greetings()					// Funkcja wyświetlajśca na ekranie nagłówek programu
{
	printf("==========================================================================================\n||\t\t\t\t\t\t\t\t\t\t\t||\n");
	printf("||  Podaj macierz kwadratowa [4 x 4], dla ktorej chcesz obliczyc macierz odwrotna:\t||\n");
	printf("||  (kolejnosc wprowadzania: kolejne elementy wierszy, poczawszy od a11)\t\t||\n");
    printf("||  (zakres dopuszczalnych wartosci elementow od -999.99 do 999.99\t\t\t||\n");
	printf("==========================================================================================\n\n");
}
//==================================================================================================================================================
bool isNumber(std::string input)	// Funkcja sprawdza czy podana wartość (wejściowy ciąg znaków) jest liczbą rzeczywistą
{
	int i = 0;                      // Zmienna wskazująca na aktualnie przeglądany znak ciągu
    int dotCounter = 0  ;           // Zmienna zliczająca wystąpienia kropek w podanym ciągu
	while (input[i] != NULL)	    // Pętla przechodzi przez cały wejściowy ciąg znaków i sprawdza:
	{
	    if (input[i] == 46) dotCounter++;               // jeśli napotkany znak jest kropką to dolicz go do liczby kropek
	    if (dotCounter>1) return false;                 // jeśli wprowadzona liczba kropek jest większa niż 1 -> zwróć "fałsz"
		if ((input[i] < 48) || (input[i] > 57))			// jeżeli jakikolwiek znak nie jest cyfrą...
		{
			if ((input[i] != 45) && (input[i] != 46))	// ...jednocześnie nie bądąc znakiem " - " ani separatorem dziesiętnym (kropką)...
				return false;							// ...to funkcja zwraca wartość "fałsz" -> wejściowy ciąg znaków nie jest liczbą
			else if ((input[i] == 45) && (i > 0))		// Jeśli napotkany znak, niebędący cyfrą jest minusem, ale nie na pierwszym miejscu w ciągu
				return false;							// ...to funkcja również zwraca wartość "fałsz"

		}
		i++;                                            // przejście do kolejnego znaku
	}

	if ((i == 1)&&(((input[0]==46))||(input[0]==45))) return false;         // jeśli wprowadzoną wartośćią jest sama kropka     -> zwróć "fałsz"
	if (i == 0) return false;                           // jeśli nie wprowadzono żadnych znaków na wejściu  -> zwróć "fałsz"
	if ((std::stod(input)<(long double)-999.99)||(std::stod(input)>(long double)999.99)) return false;  // jeśli liczba jest spoza dopuszczlanego zakresu
                                                                                                        // zwróć "fałsz"

	return true;	// jeżeli program nie napotkał nigdzie na warunki zmiany flagi na "fałsz" to zwraca wartość "prawda" -> podany ciąg jest liczbą
}
//==================================================================================================================================================
double readElement()    // funkcja pobiera kolejny element macierzy ze strumienia wejścia jako łańcuch znaków i, jeśli jest on liczbą rzeczywistą
{                       // zapisaną w systemie dziesiętnym to zwróci jego wartość liczbową, w przeciwnym wypakdu będzie ponawiać żądanie podania
                        // liczby w prawidłowym formacie
	std::string input;                                  // utworzenie zmiennej na przechowywany ciąg znaków
	do {                                                // pętla każe podawać łańcuch znaków aż zostanie wprowadzony w prawidłowym formacie
		getline(std::cin, input);                       // pobranie łańcucha znaków do zmiennej "input"

		int i = 0 ;                                     // pętla sprawdza czy wejściowy ciąg znaków zawiera jakiekolwiek przecinki
		while(input[i] != NULL)                         // (np jako separatory dziesiętne) i konwertuje je na kropki. Później funkcja
        {                                               // inNumber() sprawdzi czy całość ciągu jest prawidłowo sformatowana.
            if (input[i] == 44) input[i] = 46;          //
            i++;                                        //
        }

		if (!isNumber(input))                           // jeśli podany ciąg nie jest prawidłowym formatem liczby dziesiętnej to:
		{
			std::cout<< "\033[8;17f";                   // ustawienie kursora w pozycji [8,17] ekranu konsoli i nadpisanie znajdującej się tam
			std::cout<< "                                                                            "; // wartości "spacjami (barbarzyństwo ale działa)
			std::cout<< "\033[7;17fNiewlasciwe dane - POPRAW!"; // ustawienie kursora w pozycji [7,17] i wyświetlenie komunikatu o błędnych danych wejściowych
			std::cout<< "\033[8;17f";                   // ponowne ustawienie kursora w pozycji [8,17], gdzie ma być ponownie podana wartość wejściowego łańcucha
		}
	} while (!isNumber(input));                         // warunek powtarzania pętli tak długo jak zmienna input nie będzie prawidłowo zapisaną liczbą

	return std::stod(input);                            // wyjście z pętli poprzez podanie prawidłowo zapisanej liczby dziesiętnej i zwrócenie przez
}                                                       // funckję wartości stod (string to double), która przetwarza liczbę zapisaną w łańcuchu znaków
                                                        // na typ liczby rzeczywistej podwójnej precyzji
//==================================================================================================================================================
int countDigits(long double a, short prec)							// Funkcja zlicza cyfry części całkowitej podanej liczby rzeczywistej
{                                                                                    // z uwzględnieniem przyjętej precyzji wyświetlania(!!! ISTOTNE !!!)

	unsigned long long b = (unsigned long long int)abs(a);			// W pierwszej kolejności rzutuje liczbę rzeczywistą na typ całkowity

	if (b<1) return 1;
        long double absA = a ;                                      // zmienna "absA" przechowuje wartość bezwzględną liczby "a"
        if (absA<0) absA = -absA;                                   // jeśli wartość "a" jest mniejsza od 0 to jej modułem jest liczba przeciwna

	long double rest = absA - b;                                    // zmienna "rest" przechowuje wartość ułamkową liczby a

	if((prec==1)&&((rest*10)>5)) b++;

	else
    {
        for (int i = 1; i <= prec+1; i++)                           // część dziesiętna liczby "a" jest mnożona przez 10 o jeden raz więcej niż
            rest *= 10;                                              //  liczba znaków precyzji, którą chcemy wyświetlać na ekranie

        std::string strRest = std::to_string(rest);                 // pomocnicza zamiana wymnożonej przez wielokrotność 10 reszty na łańcuch znaków
        int i = 0 ;
        while(strRest[i] == 57)                                     // jeśli kolejne znaki (oryginalnie po przecinku) są dziewiątkami
        {
            if((i==prec-1)&&((strRest[i+1])>53)&&(strRest[i+1<58])) // ...a kolejna po ostatniej wyświetlanej jest większa od 5 (zaokrąglenie w górę)
            {
                b++ ;                                               // ...to bazowa wartość z której wyliczamy liczbę znaków części całkowitej zostaje zwiększona o 1
                break;                                              // (szczególny przypadek np. 9.999 przy precyzji wyświetlania 2 znaków po przecinku zostanie wyświetlone
            }                                                       // jako 10.00, przez co długość części dziesiętnej zwiększa się o 1. Jeśli nie uwzględnić tego przypadku to
            i++;                                                    // tabelki się brzydko rozjeżdżają
        }
    }

	int digits = 1;									// liczba nie może mieć mniej znaków dziesiętnych niż 1 (0.1 nadal ma jeden znak przed przecinkiem)

        while (b >= 10)								// pętla dzieli zrzutowaną liczbę przez 10 aż wynik będzie mniejszy od 10, czyli będzie miał tylko jeden znak...
        {
		digits++;									// ...zliczając jednocześnie ile takich operacji należało wykonać
		b /= 10;
	}
	return digits;									// funkcja zwraca liczbę wykonanych dzieleń - jest to liczba cyfr w części całkowitej liczby "a"
}                                                   // dla liczby, której moduł jest mniejszy od 1 również jest zwracana liczba 1, gdyż 0 stanowi składową liczby

int countTotal(long double a, short precision)        // funkkcja zwraca ilość wszystkich znaków tworzoących liczbą (niezbędna informacja do prawidłowego formatowania
{                                                   // wyświetlanych wyników

	int tmpCount = countDigits(a,precision)+precision+1;    // zmienna "tmpCount" pobiera informację o liczbie cyfr częśći całkowitej rozpatrywanej liczby "a"
                                                            // ...dolicza do niej liczbę wyświetlanych znaków precyzji i znak kropki (+1)
	if (a < 0) tmpCount++;                                  // jeśli liczba jest ujemna to należy zwiększyć jej długość o 1 na znak "-" (minus)
	return tmpCount;                                        // zwracanie przez funkcję liczby całkowitej -> całkowitej liczby znaków potrzebnych do wyświetlenia liczby

}
//==================================================================================================================================================

int printRow(int prec, int *maxWidth,long double row[4], bool rowStat[4])	// Funkcja rysuje wiersz przy wyświetlaniu macierzy na ekranie;
{                                                                           // funkcja pobiera dane:
                                                                            //    prec: precyzję wyświetlania wyników
                                                                            //    *maxWidth: wskaźnik na tablicę z wartościami najdłuższych liczb w każdej kolumnie
                                                                            //    row[4]: czteroelementowa tablica: wiersz macierzy
                                                                            //    rowStat[4]:   czteroelementowa tablicz: wiersz macierzy z informacją o tym czy
                                                                            //                  rozpatrywany element został już wprowadzony

	std::cout << std::setprecision(prec) << std::fixed;                     // ustawienie precyzji strumienia wyjścia na wartość zmiennej "prec"
	int totLength = 10;                                                     // zmienna przechowująca informację o całkowitej długości wiersza (wartość początkowa uzależniona
                                                                            // od przewidzianych przerw między wyświetlanymi elementami i znaków " | " początku i końca wiersza
	printf("\t|  ");                                                        // "otwarcie" wiersza znakiem " | "
	for (int i = 0; i < 4; i++)                                             // 4 - krotne wykonanie pętli wypisującej znak na ekranie
	{
		totLength += maxWidth[i];                                           // zwiększenie zmiennej "totLength" o długość (szerokość) najdłuższego elementu w kolumnie
		if (rowStat[i] == true)                                             // jeśli aktualny element został już wprowadzony to:
		{
			int tmpDiff = maxWidth[i] - countTotal(row[i], prec);           // zmienna pomocnicza wyznaczająca różnicę (wyrażoną w ilości znaków) między długośćią (szerokością)...
                                                                            // ...najdłuższego elementu w kolumnie a długością aktualnie rozpatrywanego elementu. Zmienna określa...
                                                                            // ...ile "spacji" należy "dopisać" aby wyrównać różnicę między długościami tych elementów
			while (tmpDiff > 0)                                             // tak długo aż ta różnica istanieje (jest większa od 0) to
			{
				printf(" ");                                                // "dopisuj" puste znaki ...
				tmpDiff--;                                                  // ...i zmniejszaj wartość zmiennej pomocniczej "tmpDiff"
			}
			std::cout << row[i] << "  ";                                    // po "wyrównaniu" pozycji kursora wypisz wartość aktualnego elementu;
		}
		else                                                                // jeśli element nie został jeszcze wprowadzony (jego status to "fałsz")
		{
			int tmpDiff = maxWidth[i] - 3;									// 3 znaki szerokości dla oznaczenia niewypełnionego elementu macierzy ("___")
			while (tmpDiff > 0)                                             // analogicznie jak powyżej wypełnianie "spacjami" różnicy między szerokością najdłuższego elelemntu kolumny...
			{                                                               // ...a szerokością aktualnego elementu
				printf(" ");
				tmpDiff--;
			}
			std::cout << "___" << "  ";                                     // po wyrównaniu różnicy wypisanie "blanka" na ekranie

		}
	}
	printf("|\n");                                                          // zamknięcie wiersza znakiem "|" i przejściem do nowego wiersza
	return totLength;                                                       // funkcja zwraca jako wartość długość (ilość znaków) całkowitą wiersza
}
//==================================================================================================================================================
