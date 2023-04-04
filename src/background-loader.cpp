
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

const std::string BackgroundLoader::BackgroundDirectory = "bgr/";

// assume the container has size (h * w)
void BackgroundLoader::load(std::string& fname, char** ans) {
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
	std::ifstream fin(fname);
	while (!fin.eof()) {
		std::string line;
		getline(fin, line, '\n');

		int len = line.length();
		if (len > w) len = w;
		if (len > col) col = len;

		for (int x = 0; x < len; x++) map[row][x] = line[x];
		if (++row > h) break;
	}

	// clone to container
	int p = (w - col) >> 1;	// padding
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < p; x++) ans[y][x] = ' ';
		for (int x = p; x < w - p; x++) ans[y][x] = map[y][x - p];
		for (int x = w - p; x < w; x++) ans[y][x] = ' ';
	}

	// free
	for (int y = 0; y < h; y++) delete[] map[y];
	delete[] map;
}

void BackgroundLoader::load(int id, char** ans) {
	Array<std::string> ls = FileFetcher::ls(BackgroundDirectory);
	load(ls[id], ans);
}

void BackgroundLoader::rand_load(char** ans) {
	Array<std::string> ls = FileFetcher::ls(BackgroundDirectory);
	load(ls[rand() % ls.len], ans);
}
