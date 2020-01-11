#ifndef _XYIO_

#pragma warning(disable:4244)
#pragma warning(disable:4996 4005)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#ifndef __cplusplus
#include <stdlib.h>
#include <stdio.h>
#else
#include <cstdlib>
#include <cstdio>
using namespace std;
#endif

#include "xyio.h"

#endif

int main(void)
{
	printf("Michal Zapart\n");
	printf("nacisnij dowolny klawisz, aby kontynuowac . . . ");
	getchar();

	int maxx, maxy;
	char text[120];
	int x, y;
	clear();
	getrange(&maxx, &maxy);

	xyprintf(maxx - 20, maxy - 20, "wyswietlanie wlasnej funkcji\n\t\t<= wprowadz tekst po lewej.");
	getcursor(&x, &y);
	xyscanf(0, y, "%s", text);

	x = maxx / 2;
	y = maxy / 2;
	setcursor(x, y);
	printf("%s", text);

	getchar();
	printf("\n\n\nkoniec programu.\n");
	return 0;
}
