
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

	for (int y = 0; y < h; y++) {
		map[y] = new char[w];
		fgc[y] = new char[w];
		bgc[y] = new char[w];
	}

	clrmap();
}

void Renderer::clrmap() {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			map[y][x] = ' ';
			fgc[y][x] = White;
			bgc[y][x] = Black;
		}
	}
}

void Renderer::render() {
	clrscr();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			printf("\033[4%c;3%cm%c", bgc[y][x], fgc[y][x], map[y][x]);
		}
		printf("\n");
	}
}

#if __linux__	// ------------------------------
void Renderer::clrscr() {
	system("clear");
}
#elif _WIN32	// ------------------------------
void Renderer::clrscr() {
	system("cls");
}
#endif			// ------------------------------
