
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Mar 21 08:45:05 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "renderer.h"

Renderer::Renderer() {
	map = new char*[h];
	fgc = new char*[h];
	bgc = new char*[h];
	thk = new char*[h];
	usg = new bool*[h];

	for (int y = 0; y < h; y++) {
		map[y] = new char[w];
		fgc[y] = new char[w];
		bgc[y] = new char[w];
		thk[y] = new char[w];
		usg[y] = new bool[w];

		for (int x = 0; x < w; x++) {
			map[y][x] = ' ';
			fgc[y][x] = Color::White;
			bgc[y][x] = Color::Black;
			thk[y][x] = Color::Regular;
			usg[y][x] = 1;
		}
	}
}

void Renderer::render() {
	clrscr();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (usg[y][x] == UseBackground) Color::setfb(fgc[y][x], bgc[y][x]);
			else Color::setft(fgc[y][x], thk[y][x]);
			printf("%c", map[y][x]);
		}
		printf("\n");
	}
}

void Renderer::clrscr() {
#if __linux__
	system("clear");
#elif __APPLE__
	system("clear");
#elif _WIN32
	system("cls");
#endif
}
