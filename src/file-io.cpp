
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Fri Mar 31 17:35:19 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "file-io.h"

bool FileIO::read_lvl(const char* fname, uint8_t**& map, uint8_t& h, uint8_t& w) {
	std::ifstream in(fname, std::ios::in | std::ios::binary);

	if (!in.is_open()) return false;

	int h32, w32, *map32;

	in.read(reinterpret_cast<char*>(&h32), sizeof(h32));
	in.read(reinterpret_cast<char*>(&w32), sizeof(w32));
	map32 = new int[h32 * w32];

	for (int i = 0; i < h32; i++)
		for (int j = 0; j < w32; j++)
			in.read(reinterpret_cast<char*>(&map32[i*w32 + j]), sizeof(map32[0]));
	in.close();

	convert(map32, h32, w32, map, h, w);
	delete[] map32;
	return true;
}

// f teamwork
void FileIO::convert(int* map32, int h32, int w32, uint8_t**& map, uint8_t& h, uint8_t& w) {
	h = static_cast<uint8_t>(h32);
	w = static_cast<uint8_t>(w32);

	map = new uint8_t*[h];

	for (int y = 0; y < h32; y++) {
		map[y] = new uint8_t[w];
		for (int x = 0; x < w32; x++)
			map[y][x] = static_cast<uint8_t>(map32[w32*y + x] - 'A' + 1);
	}
}
