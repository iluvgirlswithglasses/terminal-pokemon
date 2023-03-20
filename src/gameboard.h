
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
#include "deque.cpp"

/*
@ about this:
	operates the gameboard
*/

struct GameBoard {
public:
	/**
	 * @ special values
	 * */
	static constexpr uint8_t EmptyCell = 0;
	static constexpr int MSK8 = (1<<8) - 1;	// 1111 1111

	// the game map & its size
	uint8_t h, w;
	uint8_t** map;

	// constructors & deconstructors
	GameBoard(uint8_t _h, uint8_t _w, uint8_t** gamedata);
	~GameBoard();

	// check if (y0, x0) can be matched with (y1, x1)
	bool validate(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1);

	// brute force to find a matching pair (y0, x0) (y1, x1)
	// returns in following format:
	// 		(y0<<24) | (x0<<16) | (y1<<8) | (x1<<0)
	uint32_t suggest();

	// get the path from (y0, x0) -> (y1, x1)
	// which was previously traced
	Deque<uint16_t> get_path(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1);

private:
	// get_path() dfs trace
	void traceDFS(Deque<uint16_t> &q, uint8_t dy, uint8_t dx, uint8_t y, uint8_t x, uint8_t d);
	// encodes (y, x)
	uint16_t key(uint8_t y0, uint8_t x0) { return static_cast<uint16_t>(y0)<<8|x0; }

	/**
	 * @ BFS
	 * */
	bool*** vst;
	uint32_t*** trace;

	void prepBFS();
	void deprebBFS();
	void resetVst();

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

#endif	// GAMEBOARD_H
