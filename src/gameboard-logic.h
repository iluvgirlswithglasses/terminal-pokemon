
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Mar 21 18:54:23 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef GAMEBOARD_LOGIC_H
#define GAMEBOARD_LOGIC_H
// ------------------------------------------------------------

#include <cstdint>
#include "deque.cpp"

/*
@ about this:
	validate moves, suggest moves, trace moves
*/

class GameboardLogic {
public:
	// this mask is necessary for coord encoding in every gameboard logic module
	static constexpr int MSK8 = (1<<8) - 1;	// 1111 1111

	GameboardLogic() {}

	// check if (y0, x0) can be matched with (y1, x1)
	virtual bool validate(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) { return 0; }

	// brute force to find a matching pair (y0, x0) (y1, x1)
	// returns in following format:
	// 		(y0<<24) | (x0<<16) | (y1<<8) | (x1<<0)
	virtual uint32_t suggest() { return 0; }

	// get the path from (y0, x0) -> (y1, x1)
	// which was previously traced
	virtual Deque<uint16_t> get_path(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) { return Deque<uint16_t>(); }

protected:
	// the game map & its size
	uint8_t h, w;
	uint8_t** map;
};

#endif	// GAMEBOARD_LOGIC_H
