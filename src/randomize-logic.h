\
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Thu Mar 30 18:39:01 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef RANDOMIZE_LOGIC_H
#define RANDOMIZE_LOGIC_H
// ------------------------------------------------------------

#include <cstdint>
#include <random>
#include "deque.h"
#include "array.h"
#include "gameboard.h"

struct RandomizeLogic {
public:
	RandomizeLogic(Gameboard* board);

	/**
	 * shuffle the board
	 * this modifies the gameboard
	 * 
	 * return a deque of affected cells
	 * format (from_y << 24) | (from_x << 16) | (to_y << 8) | (to_x)
	 * */
	Array<uint32_t> randomize();

private:
	Gameboard* board;

	bool legit(uint8_t y, uint8_t x) {
		return 0 < y && y < board->h - 1 && 0 < x && x < board->w - 1;
	}
};

#endif	// RANDOMIZE_LOGIC
