
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Mar 21 10:02:44 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef GAMEBOARD_RENDERER_H
#define GAMEBOARD_RENDERER_H
// ------------------------------------------------------------

/*
@ about this:
	draw the gameboard into the screen grid

	note that this object does not care about the screen size
	so beware of indexing
*/

#include <cstdint>
#include <cstdio>
#include "color.h"
#include "gameboard.h"
#include "renderer.h"

struct GameboardRenderer {
public:
	uint8_t** map;			// the gameboard
	char**    scr;			// the screen
	uint8_t   row, col;		// the size of the gameboard
	uint8_t   top, lft;		// where the gameboard is projected on the screen

	GameboardRenderer(uint8_t** map, char** scr, uint8_t row, uint8_t col, uint8_t top, uint8_t lft);
	void burn();			// burns the gameboard into the screen grid

private:
	static constexpr uint8_t CellSize = 7;	// size of a cell on screen grid

	void draw_cell(uint8_t y, uint8_t x);	// draws tile map[y, x]
	void draw_empty_cell(uint8_t y, uint8_t x);

	uint8_t get_ry(uint8_t y) { return top + CellSize * y };
	uint8_t get_rx(uint8_t x) { return lft + CellSize * x };
};

#endif	// GAMEBOARD_RENDERER_H
