
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Mar 20 11:15:01 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H
// ------------------------------------------------------------

#include <cstdint>
#include <cstring>

/*
@ about this:
	operates the gameboard
*/

struct Gameboard {
public:
	/**
	 * @ special values
	 * */
	static constexpr uint8_t EmptyCell = 0;

	// the game map & its size
	uint8_t h, w;
	uint8_t** map;
	int remaining;

	// constructors & deconstructors
	Gameboard(uint8_t _h, uint8_t _w, uint8_t** gamedata);
	~Gameboard();

	// calculate the current score 
	int calc_score() {
		int ans = (h - 2) * (w - 2);
		for (uint8_t y = 1; y < h - 1; y++)
			for (uint8_t x = 1; x < w - 1; x++)
				if (map[y][x] != EmptyCell) ans--;
		return ans;
	}
};

#endif	// GAMEBOARD_H
