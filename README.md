# TheMatrix - PL
===================================================================================================
Program The Matrix wykonany w ramach zajęć projektowych z przedmiotu Techniki Programowania

Prowadzący:	dr hab. inż. Zbigniew Łubniewski
		Katedra Systemów Geoinformatycznych
		Wydział Elektroniki, Telekomunikacji i Informatyki
		Politechnika Gdańska

Autor projektu:	Adam Chojaczyk
		Nr indeksu 183269
		Kierunek: Informatyka, studia niestacjonarne
		Wydział Elektroniki, Telekomunikacji i Informatyki
		Politechnika Gdańska
		Rok I, semestr 2
		Roka akademicki 2019/2020

===================================================================================================

PRZEZNACZENIE PROGRAMU:

Zadaniem programu jest, dla zadanej macierzy 4. stopnia: 
 - obliczenie wyznacznika
 - macierzy odwrotnej
 - prezentacja wyników na ekranie konsoli

===================================================================================================

URUCHOMIENIE I DZIAŁANIE PROGRAMU:

Program jest uruchamiany w konsoli, kompatybilnej z systemem operacyjnym MS Windows(R) 10.

===============================	Dla przejrzystości działania zalecane jest uruchamianie
	 UWAGA!!! 		programu w zmaksymalizowanym oknie konsoli przy szerokości
===============================	konsoli nie mniejszej niż 90 znaków.

Uruchomienie programu następuje poprzez:
 - uruchomienie pliku TheMatrix.exe z poziomu przeglądarki plików, lub
 - uruchomienie pliku TheMatrix.exe bezpośrednio z konsoli Windows(R).

Po uruchomieniu użytkownikowi ukazuje się komunikat o przeznaczeniu programu oraz uproszczona 
instrukcja dotycząca wprowadzania danych:
 - kolejność wprowadzania elementów macierzy,
 - informacja o ograniczeniu wielkości podawanych elementów.

Uzupełnianie macierzy następuje poprzez wprowadzenie kolejnych wierszy.
Kolejność wierszy: od góry do dołu macierzy, przy czym element w wierszach są uzupełniane
od lewej do prawej.

Po uzupełnieniu wszystkich elementów macierzy program oblicza wartość wyznacznika macierzy:
- jeśli wartość wyznacznika jest równa zero to znaczy, że macierz jest osobliwa i nie posiada
macierzy odwrotnej. Program informuje o tym fakcie,
- jeśli wartość wyznacznika jest niezerowa to następuje obliczenie macierzy dopełnień algebraicznych,
a następnie na jej podstawie obliczana jest macierz odwrotna do macierzy wejściowej. Wyniki tych
obliczeń, wyznacznika i macierzy odwrotnej, prezentowane są na ekranie konsoli. 

Niezależnie od tego, czy macierz jest osobliwa i nie posiada macierzy odwrotnej, czy też nie,
po zakończeniu obliczeń program, pod wynikami obliczeń wyświetla komunikat o możliwości dopasowania
precyzji wyświetlanych wyników, lub wyjściu z programu.

===================================================================================================

OBSŁUGA PROGRAMU:

wprowadzanie danych:

wprowadzanie danych następuje poprzez wpisanie na klawiaturze wartości do wprowadzenia
i zatwierdzenie jej naciśnięciem klawisza [enter].

W przypadku wprowadzenia danych niezgodnych z zakresem lub nieprawidłowo sformatowanych zostaną
one zignorowane oraz zostanie wyświetlony komunikat o wprowadzeniu nieprawidłowych danych
i konieczności ich poprawienia.

Po uzupełnieniu wszystkich elementów macierzy program wykonuje obliczenia i prezentuje na ekranie
wyniki:
 - informację o zerowym wyznaczniku, macierzy osobliwej i braku macierzy do niej odwrotnej, lub
 - wartość wyznacznika oraz postać macierzy odwrotnej do macierzy wejściowej.

Po wyświetleniu na ekranie wyników, pod nimi zostaje wyświetlona instrukcja o możliwości:
 - zmiany precyzji (liczby miejsc po przecinku) wyświetlanych wyników,
 - zakończenia programu.

Od tej pory jakiekolwiek działanie może być spowodowane poprzez wciśnięcie klawiszy:
 "+" (plus) - 	zwiększenie precyzji wyświetlanych wyników, szczególnie przydatne przy dużych
		wartościach wyznacznika, gdzie elementy macierzy odwrotnej mają bardzo małe wartości
		domyślnie ustawiona maksymalna precyzja to 18 znaków.

 "-" (minus) - 	zmniejszenie precyzji wyświetlanych wyników, domyślnie ustawiona minimalna
		precyzja to 1 znak.

 "q" lub "Q" - 	od "QUIT" - wciśnięcie jednego z podanych klawiszy spowoduje zakończenie działania 
		programu.

Wiśnięcie któregokolwiek innego klawisza jest ignorowane przez program.

Po wciśnięciu znaków "+" lub "-" program zmienia wartość parametru odpowiedzialnego za ilość miejs
po przecinku dziesiętnym, które mają być wyświetlane, czyści ekran a następnie od nowa prezentuje 
wyniki ze zmienioną precyzją wyświetlania. Przez ten proces na ekranie jest widoczne "mrugnięcie"
podczas zmiany wartości precyzji.

===================================================================================================

FORMAT DANYCH WEJŚCIOWYCH:

program przewiduje prowadzenie obliczeń dla liczb rzeczywistych z zakresu <-999.99 , 999.99>
zatem wprowadzane dane powinny mieścić się w podanym zakresie i być wprowadzane z zachowaniem 
następującego formatowania:

<znak minus dla liczb ujemnych><część całkowita liczby><separator dziesiętny><część ułamkowa liczby>

przy czym:

<znak minus dla liczb ujemnych> jak opis wskazuje podajemy znak minus dla liczb ujemnych, jednak
program nie zaakceptuje dodawania znaku plus "+" dla liczb dodatnich lub zera i wyświetli komunikat
z prośą o korektę danych,

<część całkowita liczby> musi mieścić się w zakresie <0 , 999> a w przypadku jej niepodania program
sam wstawi w jej miejscu zero, np "-.123" zostanie zinterpretowane jako "-0.123"

<separator dziesiętny> w pamięci komputera program wykorzystuje kropkę "." jako separator dziesiętny
jednak ze względu na różne nawyki użytkowników i chęć "zuniwersalizowania" obsługi, jeśli użytkownik
poda przecinek "," jako separator dziesiętny to program przekonwertuje go sobie na kropkę ".",

<część ułamkowa liczby> ze względu na przyjęty w programie typ danych dla macierzy podstawowej (long
double) nie powinna zawierać więcej niż 18 znaków precyzji. Domyślna precyzja wyświetlanych wyników 
wynosi 2 miejsca po przecinku i może być zmieniana z poziomu obsługi programu, po zaprezentowaniu
wyników obliczeń. Analogicznie jak dla części całkowitej, jeśli nie zostanie ona wprowadzona (nawet
w przypadku wprowadzenia znaku separatora dziesiętnego) to domyślnie zostanie ustawiona jako 0, np:
wprowadzenie ciągu znaków "123." zostanie zinterpretowane jako "123.00"

DOPUSZCZALNE ZNAKI:
 - cyfry: 0 1 2 3 4 5 6 7 8 9
 - znaki: - , . 
przy czym nieakceptowalne jest:
* podanie znaku "-" (minus) w innym niż na pierwszym miejscu lub jako jedynego znaku w ciągu
* podanie znaku "." lub "," więcej niż jeden raz lub jako jedynego znaku w ciągu

