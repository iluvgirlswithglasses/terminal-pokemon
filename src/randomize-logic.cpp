
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Thu Mar 30 18:49:19 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "randomize-logic.h"

RandomizeLogic::RandomizeLogic(Gameboard* _b) {
	board = _b;
	srand(time(0));
}

Deque<uint32_t> RandomizeLogic::randomize() {
	// move rules
	static constexpr int 
		RC = 4,
		RY[RC] = { -1, 0, 1, 0, },	// adj `y` cells {t, l, d, r}
		RX[RC] = { 0, -1, 0, 1, };	// adj `x` cells {t, l, d, r}

	Deque<uint32_t> history;

	for (uint8_t y = 1; y < board->h - 1; y++)
	for (uint8_t x = 1; x < board->w - 1; x++)
	if (board->map[y][x] != Gameboard::EmptyCell) {
		for (int t = 0; t < RC; t++) {
			uint8_t ny = y + RY[t], nx = x + RX[t];
			if (board->map[ny][nx] != Gameboard::EmptyCell) continue;
			if (!legit(ny, nx)) continue;
			if (rand() % 6 < 5) continue;	// too simple, the distribution is not even

			// move `(y, x)` to `(ny, nx)` (`(ny, nx)` is currently an empty cell)
			board->map[ny][nx] = board->map[y][x];
			board->map[y][x] = Gameboard::EmptyCell;
			history.push_back( (y<<24)|(x<<16)|(ny<<8)|(nx) );

			break;
		}
	}

	return history;
}
