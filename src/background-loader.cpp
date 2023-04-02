
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Sat Apr  1 19:14:02 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "background-loader.h"

// assume the container has size (h * w)
void BackgroundLoader::load(const char* fname, char** container) {
	static constexpr int h = Param::ScreenHeight, w = Param::ScreenWidth;

	// create holder
	char** map = new char*[h];
	for (int y = 0; y < h; y++) {
		map[y] = new char[w];
		for (int x = 0; x < w; x++) map[y][x] = ' ';
	}
	int row = 0;
	int col = 0;

	// read file
	FILE* fin = fopen(fname, "r");
	size_t  linesiz = 0;
	char*   linebuf = 0; 
	ssize_t linelen = 0;

	while ((linelen = getline(&linebuf, &linesiz, fin)) > 0) {
		linelen--;	// exclude '\n'
		if (linelen > w) linelen = w;
		if (linelen > col) col = linelen;

		memcpy(map[row], linebuf, sizeof(linebuf[0]) * linelen);
		free(linebuf);
		linebuf = NULL;
		if (++row >= h) break;
	}

	// clone to container
	int p = (w - col) >> 1;	// padding
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < p; x++) container[y][x] = ' ';
		for (int x = p; x < w - p; x++) container[y][x] = map[y][x - p];
		for (int x = w - p; x < w; x++) container[y][x] = ' ';
	}

	// free
	for (int y = 0; y < h; y++)
		delete[] map[y];
	delete[] map;
}
