
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
	map = new char*[H];
	fgc = new char*[H];
	bgc = new char*[H];

	for (int y = 0; y < H; y++) {
		map[y] = new char[W];
		fgc[y] = new char[W];
		bgc[y] = new char[W];
	}

	clrmap();
}

void Renderer::clrmap() {
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			map[y][x] = ' ';
			fgc[y][x] = White;
			bgc[y][x] = Black;
		}
	}
}

void Renderer::render() {
	clrscr();
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			printf("\033[4%c;3%cm", bgc[y][x], fgc[y][x]);
			putchar(map[y][x]);
		}
		putchar('\n');
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
