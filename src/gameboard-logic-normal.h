
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Mar 21 18:58:27 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef GAMEBOARD_LOGIC_NORMAL_H
#define GAMEBOARD_LOGIC_NORMAL_H
// ------------------------------------------------------------

#include <cstring>
#include "gameboard-logic.h"

/*
@ about this:
	operates the game on normal difficulty
	which means... the only accepted matching patterns are:
	I, L, U, Z shapes
*/

class GameboardLogicNormal: public GameboardLogic {
public:
	GameboardLogicNormal(uint8_t h, uint8_t w, uint8_t** map);
	~GameboardLogicNormal();
	bool validate(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) override;
	uint32_t suggest() override;
	Deque<uint16_t> get_path(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) override;

private:
	// get_path() dfs trace
	void traceDFS(Deque<uint16_t> &q, uint8_t dy, uint8_t dx, uint8_t y, uint8_t x, uint8_t d);

	/**
	 * @ BFS
	 * */	
	static constexpr int MaxDepth = 2;	// maximum turns

	uint8_t*** vst;
	uint32_t*** trace;

	// reset memory allocation for vst
	void reset_vst();

	// if fixed == false:
	// 		finds (y1, x1) which (y0, x0) can be matched with
	// 		if there is no such cell, returns 0
	// if fixed == true:
	// 		check if (y0, x0) can be matched with (y1, x1)
	// return format:
	// 		y<<8|x
	uint16_t BFS(uint8_t y0, uint8_t x0) { return BFS(y0, x0, false, 0, 0); }
	uint16_t BFS(uint8_t y0, uint8_t x0, bool fixed, uint8_t y1, uint8_t x1);
};

#endif	// GAMEBOARD_LOGIC_NORMAL_H
