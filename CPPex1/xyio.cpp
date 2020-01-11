

#include "xyio.h"


//ustawienie koordynatów kursora
void setcursor(int x, int y)
{
	//wskaŸnik na ekran 
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);

	//zmienna przechowuj¹ca koordynaty
	COORD punkt = { x,y };

	//ustawienie kursora na pozycji 
	SetConsoleCursorPosition(ekran, punkt);
}

//pobranie informacji o kursorze i przekazanie ich do zewnêtrznych zmiennych
void getcursor(int* x, int* y)
{
	//wskaŸnik na ekran 
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	// zmienna gdzie bêdzie wczytany bufor informacji
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	//wczytanie danych do bufora na temat ekranu konsoli
	GetConsoleScreenBufferInfo(ekran, &bufor);
	//ustawienie pozycji kursora do zmiennych
	*x = bufor.dwCursorPosition.X;
	*y = bufor.dwCursorPosition.Y;
}

// ustawienie zakresu rozdzielczoœci okna i przekazanie go do zew. zmiennych
void getrange(int* maxx, int* maxy)
{
	//wskaŸnik na ekran
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	//bufor do wczytania danych
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	//pobranie informacji 
	GetConsoleScreenBufferInfo(ekran, &bufor);
	//wczytanie ich do zmiennych
	*maxx = bufor.dwMaximumWindowSize.X;
	*maxy = bufor.dwMaximumWindowSize.Y;
}

//srwindow - Struktura SMALL_RECT zawieraj¹ca wspó³rzêdne lewego górnego i prawego dolnego rogu okna w buforze ekranu konsoli.
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


// "..." lista argumentów
// listê argumentów bêdziemy przechowywaæ w obiekcie va_list
// przegl¹d wszystkich argumentów rozpoczynamy uruchamiaj¹c funkcjê va_start(nazwaListy, pierwszyArgument);
// Poszczególne dane odczytywane s¹ za pomoc¹ funkcji va_arg(nazwaListy, typDanych);
// na koñcu wymagane jest zamkniêcie naszej listy za pomoc¹ va_end(nazwaListy);

//wczytywanie tekstu do zewnêtrznej zmiennej, które odbywa siê w specyficznym miejscu na konsoli { x , y }
int xyscanf(int x, int y, const char* format, ...)
{
	//uchwyt do klawiatury 
	HANDLE klawiatura = GetStdHandle(STD_INPUT_HANDLE);
 


	va_list argumenty;
	int rezultat;
	// format -  "%s"

	va_start(argumenty, format);
	setcursor(x, y);

	//Odczytuje sformatowane dane z ci¹gu.
	// tekst - przechowywane dane 
	//format - ci¹g kontroli formatu  "%s"
	//arg - lista argumentów zmiennych czyli zmienna na tekst z poza funkcji 
	rezultat =  vfscanf(stdin, format, argumenty);

	va_end(argumenty);
	return rezultat;
}


//wypisanie danych na ekran w podanym punkcie konsoli
int xyprintf(int x, int y, const char* format, ...)
{
	//wskaŸnik na ekran
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);

	va_list argumenty;
	int rezultat;

	va_start(argumenty, format);
	//wpisanie na ekran tego co podano w liœcie argumentów 
	rezultat = vfprintf(stdout, format, argumenty);
	
	va_end(argumenty);
	return rezultat;
}

void clear(void)
{
	//wskaŸnik na ekran - uchwyt
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	COORD poczatek = { 0,0 };
	DWORD znaki;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	//wype³nienie konsoli pustym znakiem spacji, od pozycji 0,0 do maksymalnego rozmiaru
	FillConsoleOutputCharacter(ekran, ' ', bufor.dwSize.X * bufor.dwSize.Y, poczatek, &znaki);
	SetConsoleCursorPosition(ekran, poczatek);
}
