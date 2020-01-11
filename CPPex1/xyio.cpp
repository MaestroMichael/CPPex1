

#include "xyio.h"


//ustawienie koordynat�w kursora
void setcursor(int x, int y)
{
	//wska�nik na ekran 
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);

	//zmienna przechowuj�ca koordynaty
	COORD punkt = { x,y };

	//ustawienie kursora na pozycji 
	SetConsoleCursorPosition(ekran, punkt);
}

//pobranie informacji o kursorze i przekazanie ich do zewn�trznych zmiennych
void getcursor(int* x, int* y)
{
	//wska�nik na ekran 
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	// zmienna gdzie b�dzie wczytany bufor informacji
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	//wczytanie danych do bufora na temat ekranu konsoli
	GetConsoleScreenBufferInfo(ekran, &bufor);
	//ustawienie pozycji kursora do zmiennych
	*x = bufor.dwCursorPosition.X;
	*y = bufor.dwCursorPosition.Y;
}

// ustawienie zakresu rozdzielczo�ci okna i przekazanie go do zew. zmiennych
void getrange(int* maxx, int* maxy)
{
	//wska�nik na ekran
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	//bufor do wczytania danych
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	//pobranie informacji 
	GetConsoleScreenBufferInfo(ekran, &bufor);
	//wczytanie ich do zmiennych
	*maxx = bufor.dwMaximumWindowSize.X;
	*maxy = bufor.dwMaximumWindowSize.Y;
}

//srwindow - Struktura SMALL_RECT zawieraj�ca wsp�rz�dne lewego g�rnego i prawego dolnego rogu okna w buforze ekranu konsoli.
void getscreen(int* xorg, int* yorg, int* xend, int* yend)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	*xorg = bufor.srWindow.Left;
	*yorg = bufor.srWindow.Top;
	*xend = bufor.srWindow.Right;
	*yend = bufor.srWindow.Bottom;
}


// "..." lista argument�w
// list� argument�w b�dziemy przechowywa� w obiekcie va_list
// przegl�d wszystkich argument�w rozpoczynamy uruchamiaj�c funkcj� va_start(nazwaListy, pierwszyArgument);
// Poszczeg�lne dane odczytywane s� za pomoc� funkcji va_arg(nazwaListy, typDanych);
// na ko�cu wymagane jest zamkni�cie naszej listy za pomoc� va_end(nazwaListy);

//wczytywanie tekstu do zewn�trznej zmiennej, kt�re odbywa si� w specyficznym miejscu na konsoli { x , y }
int xyscanf(int x, int y, const char* format, ...)
{
	//uchwyt do klawiatury 
	HANDLE klawiatura = GetStdHandle(STD_INPUT_HANDLE);
 


	va_list argumenty;
	int rezultat;
	// format -  "%s"

	va_start(argumenty, format);
	setcursor(x, y);

	//Odczytuje sformatowane dane z ci�gu.
	// tekst - przechowywane dane 
	//format - ci�g kontroli formatu  "%s"
	//arg - lista argument�w zmiennych czyli zmienna na tekst z poza funkcji 
	rezultat =  vfscanf(stdin, format, argumenty);

	va_end(argumenty);
	return rezultat;
}


//wypisanie danych na ekran w podanym punkcie konsoli
int xyprintf(int x, int y, const char* format, ...)
{
	//wska�nik na ekran
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);

	va_list argumenty;
	int rezultat;

	va_start(argumenty, format);
	//wpisanie na ekran tego co podano w li�cie argument�w 
	rezultat = vfprintf(stdout, format, argumenty);
	
	va_end(argumenty);
	return rezultat;
}

void clear(void)
{
	//wska�nik na ekran - uchwyt
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	COORD poczatek = { 0,0 };
	DWORD znaki;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	//wype�nienie konsoli pustym znakiem spacji, od pozycji 0,0 do maksymalnego rozmiaru
	FillConsoleOutputCharacter(ekran, ' ', bufor.dwSize.X * bufor.dwSize.Y, poczatek, &znaki);
	SetConsoleCursorPosition(ekran, poczatek);
}
