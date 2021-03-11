#pragma once

void greetings();		        // Funkcja wyświetlająca nagłówek programu

bool isNumber(std::string);		// Funkcja sprawdza czy podana wartość jest liczbą rzeczywistą

double readElement();	        // Funkcja wczytuje element ze strumienia wejścia jako string i zwraca jego wartość w postaci liczby zmiennoprzecinkowej

int countDigits(long double a, short precision);	// Funkcja zlicza cyfry czêœci ca³kowitej podanej liczby rzeczywistej

int countTotal(long double a, short precision);       // Funkcja zlicza wszystkie znaki potrzebne do wypisania liczby na ekranie

int printRow(int prec, int *maxWidth, long double row[4], bool rowStat[4]);			// Funkcja rysuje wiersz przy wyświetlaniu macierzy;
