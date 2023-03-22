
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

GameboardRenderer::GameboardRenderer(uint8_t** _map, Renderer* _scr, uint8_t _row, uint8_t _col, uint8_t _top, uint8_t _lft) {
	map = _map;
	scr = _scr;
	row = _row;
	col = _col;
	top = _top;
	lft = _lft;
}

void GameboardRenderer::burn() {
	reset();
	for (int y = 0; y < row; y++)
		for (int x = 0; x < col; x++)
			if (map[y][x] > 0) draw_cell(y, x);
}

void GameboardRenderer::draw_cell(uint8_t y, uint8_t x) {
	uint8_t t = get_ry(y), 
	        d = get_ry(y+1), 
	        l = get_rx(x), 
	        r = get_rx(x+1);
	// horizontal lines
	for (int x = l; x < r; x++) {
		assign_cell_border('-', t, x);
		assign_cell_border('-', d-1, x);
	}
	// vertical lines
	for (int y = t; y < d; y++) {
		assign_cell_border('|', y, l);
		assign_cell_border('|', y, r-1);
	}
	// a '+' for each corner
	assign_cell_border('+', t, l);
	assign_cell_border('+', t, r-1);
	assign_cell_border('+', d-1, l);
	assign_cell_border('+', d-1, r-1);
	// and our main character
	constexpr uint8_t Mid = CellSize>>1;
	assign_cell_core(map[y][x], t + Mid, l + Mid);
}

void GameboardRenderer::reset() {
	// insert background image here
	// just memcpy the background instead of memset
	uint8_t t = get_ry(0), d = get_ry(row), l = get_rx(0), r = get_rx(col);
	for (int y = t; y < d; y++) 
		for (int x = l; x < r; x++)
			scr->map[y][x] = ' ';
}

/**
 * @ pixel config
 * */
void GameboardRenderer::assign_cell_border(char c, uint8_t y, uint8_t x) {
	scr->map[y][x] = c;
	scr->fgc[y][x] = Color::White;
	scr->bgc[y][x] = Color::Black;	// use bgc to trace path later
	scr->usg[y][x] = Renderer::UseBackground;
}

void GameboardRenderer::assign_cell_core(uint8_t c, uint8_t y, uint8_t x) {
	static constexpr int ViableColors = 6;
	c--;

	char color = '1' + (c % ViableColors);	// [1:6]
	char letter = 'A' + c;
	if (letter > 'Z')
		letter = letter - 'Z' - 1 + 'a';
	
	scr->map[y][x] = letter;
	scr->fgc[y][x] = color;
	scr->thk[y][x] = Color::Bold;
	scr->usg[y][x] = Renderer::UseThickness;
}
