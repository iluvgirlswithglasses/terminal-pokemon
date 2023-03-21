
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Mar 20 19:36:46 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "gameboard.h"

/**
 * @ constructors & deconstructors
 * */
Gameboard::Gameboard(uint8_t _h, uint8_t _w, uint8_t** gamedata) {
	// assume the area of the board which contains tiles has the size of _h*_w
	// then the size of `map` is (_h+2)*(_w+2), or h*w
	// which implies `map` has a 1 unit padding for each edge
	h = _h + 2, w = _w + 2;
	map = new uint8_t*[h];

	// top && down
	map[0] = new uint8_t[w];
	memset(map[0], EmptyCell, sizeof(map[0][0]) * w);
	map[h-1] = new uint8_t[w];
	memset(map[h-1], EmptyCell, sizeof(map[h-1][0]) * w);

	// paste the gamedata into the map
	for (int y = 0; y < _h; y++) {
		map[y+1] = new uint8_t[w];										// allocate this row
		map[y+1][0] = map[y+1][w-1] = EmptyCell; 						// left & right
		memcpy(map[y+1] + 1, gamedata[y], sizeof(gamedata[y][0]) * _w); // mid
	}
}

Gameboard::~Gameboard() {
	for (int y = 0; y < h; y++) delete[] map[y];
	delete[] map;
}
