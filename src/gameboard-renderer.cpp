
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Mar 21 10:02:42 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "gameboard-renderer.h"

GameboardRenderer::GameboardRenderer(uint8_t** _map, char** _scr, uint8_t _row, uint8_t _col, uint8_t _top, uint8_t _lft) {
	map = _map;
	scr = _scr;
	row = _row;
	col = _col;
	top = _top;
	lft = _lft;
}

void GameboardRenderer::burn() {
	// draw empty cells first
	for (int y = 0; y < row; y++)
		for (int x = 0; x < col; x++)
			if (map[y][x] == 0) draw_empty_cell(y, x);
	// then the tiles later
	for (int y = 0; y < row; y++)
		for (int x = 0; x < col; x++)
			if (map[y][x] > 0) draw_cell(y, x);
}

void GameboardRenderer::draw_cell(uint8_t y, uint8_t x) {

}

void GameboardRenderer::draw_empty_cell(uint8_t y, uint8_t x) {
	// insert background image here
	// just memcpy the background instead of memset
	
}
