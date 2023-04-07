
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Fri Apr  7 17:25:54 2023
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
@ usage:
	burn gameboard content to renderer
*/

#include "save-loader.h"
#include "gameboard.h"
#include "renderer.h"

struct GameboardRenderer {
	int row, col;	// the size of the gameboard
	int top, lft;	// where the gameboard is projected on the screen

	char** map = nullptr;
	Gameboard* board;
	Renderer*  rdr;

	GameboardRenderer(Gameboard* board, Renderer* rdr);
	~GameboardRenderer();

	void burn();	// burns the gameboard into the screen grid
	void reset();	// reset the screen
	void draw_border(int y, int x, char fg);

	/** @ cell configures */
	static constexpr int CellHeight = 4, CellWidth = 8;	// must be even
	static constexpr int MidY = CellHeight>>1, MidX = CellWidth>>1;

	void draw_cell(int y, int x);	// draws tile map[y, x]

	int get_ry(int y) { return top + CellHeight * y; }
	int get_rx(int x) { return lft + CellWidth * x; }

	/** @ pixel configures */
	void assign_border_pixel(char c, int y, int x, char fg);
	void assign_core_pixel(int c, int y, int x);
};

#endif	// GAMEBOARD_RENDERER_H
