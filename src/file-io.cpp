
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

bool FileIO::read_lvl(char* fname, uint8_t** map, uint8_t& h, uint8_t& w) {
	std::ifstream in(fname, std::ios::in | std::ios::binary);

	if (!in.is_open()) {
		std::cout << "level data does not exist - gamefile is corrupted\n";
		std::cout << "existing...\n";
		return false;
	}

	in.read(reinterpret_cast<char*>(&h), sizeof(h));
	in.read(reinterpret_cast<char*>(&w), sizeof(w));

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			in.read(reinterpret_cast<char*>(&map[i][j]), sizeof(map[i][j]));

	in.close();
	return true;
}
