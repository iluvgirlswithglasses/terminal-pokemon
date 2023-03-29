
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Wed Mar 29 09:19:49 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "sliding-logic.h"

SlidingLogic::SlidingLogic(Gameboard* _board, char orientation) {
	board = _board;
	switch (orientation) {
	case 't':
		yinc = -1, xinc = 0;
		break;
	case 'l':
		yinc = 0, xinc = -1;
		break;
	case 'd':
		yinc = +1, xinc = 0;
		break;
	case 'r':
	default:
		yinc = 0, xinc = +1;
		break;
	}
}

Deque<uint16_t> SlidingLogic::slide(uint8_t y0, uint8_t x0) {
	// assume that `board->map[y0][x] == EmptyCell`
	Deque<uint8_t>  elements;
	Deque<uint16_t> trace;
	uint16_t last = 0;

	// add all tiles into a deque
	for (int y = y0, x = x0; legit(y, x); y += yinc, x += xinc) {
		trace.push_back(y<<8|x);
		if (board->map[y][x] != Gameboard::EmptyCell) {
			elements.push_back(board->map[y][x]);
			board->map[y][x] = Gameboard::EmptyCell;
			last = y<<8|x;
		}
	}
	// remove redundant traces
	while (trace.count() && trace.back() != last) trace.pop_back();
	// paste the deque onto the map
	for (int y = y0, x = x0; elements.count(); y += yinc, x += xinc) {
		board->map[y][x] = elements.pop_front();
	}

	return trace;
}
