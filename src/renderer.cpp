
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
	}

	clrmap();
}

void Renderer::clrmap() {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			map[y][x] = ' ';
			fgc[y][x] = Color::White;
			bgc[y][x] = Color::Black;
			thk[y][x] = Color::Regular;
			usg[y][x] = 1;
		}
	}
}

void Renderer::wrtext(uint8_t y, uint8_t x, const char* txt) {
	uint8_t len = strlen(txt);
	for (uint8_t i = 0; i < len; i++)
		map[y][x + i] = txt[i];
}

#if __linux__	// ----------------------------------------------------------------
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
	system("clear");
}

#elif _WIN32	// ----------------------------------------------------------------
/**
 * Windows is so incredibly bad 
 * I had to write an entire section to optimize it
 * 
 * Basically, I ran this game on console, 8 colors, size 120*40
 * 
 * On native debian linux, it performed at 140fps
 * On WSL, it performed at 90fps
 * 
 * On native windows, on a same computer which ran the WSL test
 * this program performed at less than 1fps
 * 
 * I mean... WTF? HOW????
 * */
void Renderer::render() {
	/**
	 * after various experiments, I've concluded that
	 * printf() should handle invisible output
	 * while putchar should handle the visible ones
	 * */
	fflush(stdout);
	clrscr();
	for (int y = 0; y < h; y++) {
		bool preUsg = !usg[y][0];
		int  preKey = 0;

		for (int x = 0; x < w; x++) {
			int key = fgc[y][x];

			// only re-format this cell if it's different than before
			if (usg[y][x] == UseBackground) {
				key = key<<8|bgc[y][x];
				if (usg[y][x] != preUsg || key != preKey)
					Color::setfb(fgc[y][x], bgc[y][x]);
			} else {
				key = key<<8|thk[y][x];
				if (usg[y][x] != preUsg || key != preKey)
					Color::setft(fgc[y][x], thk[y][x]);
			}

			putchar(map[y][x]);

			preUsg = usg[y][x];
			preKey = key;
		}
		putchar('\n');
	}
}

void Renderer::clrscr() {
	system("cls");
}

#endif			// __linux__ _WIN32	-----------------------------------------------
