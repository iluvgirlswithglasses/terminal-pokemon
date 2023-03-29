
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Wed Mar 29 09:00:35 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef SLIDING_LOGIC_H
#define SLIDING_LOGIC_H
// ------------------------------------------------------------

#include <cstdint>
#include "deque.h"
#include "gameboard.h"

// this object modifies the gameboard
struct SlidingLogic {
public:
	SlidingLogic(Gameboard* board, char orientation);

	/*
	slides a series of cells to `(y, x)`
	the orientation of the slide is defined by `yinc`, `xinc`
	
	returns a deque of affected cells
	*/
	Deque<uint16_t> slide(uint8_t y, uint8_t x);

private:
	Gameboard* board;
	int yinc, xinc;

	bool legit(int y, int x) {
		return 0 < y && y < board->h - 1 && 
		       0 < x && x < board->w - 1;
	}
};

#endif	// SLIDING_LOGIC_H
