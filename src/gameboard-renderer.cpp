
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
	for (uint8_t y = 0; y < row; y++)
		for (uint8_t x = 0; x < col; x++)
			if (map[y][x] > 0) draw_cell(y, x);
}

void GameboardRenderer::reset() {
	// insert background image here
	// just memcpy the background instead of memset
	uint8_t t = get_ry(0), d = get_ry(row), l = get_rx(0), r = get_rx(col);
	for (uint8_t y = t; y < d; y++) 
		for (uint8_t x = l; x < r; x++)
			scr->map[y][x] = ' ';
}

/**
 * @ cells rendering
 * */
void GameboardRenderer::draw_cell(uint8_t y, uint8_t x) {
	uint8_t t = get_ry(y), l = get_rx(x);
	// draw border
	draw_border(y, x, Color::White);
	// then assign the tile
	constexpr uint8_t MidY = CellHeight>>1, MidX = CellWidth>>1;
	assign_core_pixel(map[y][x], t + MidY, l + MidX);
}

void GameboardRenderer::draw_border(uint8_t y, uint8_t x, char fg) {
	uint8_t t = get_ry(y), 
	        d = get_ry(y+1), 
	        l = get_rx(x), 
	        r = get_rx(x+1);
	// horizontal lines
	for (uint8_t x = l; x <= r; x++) {
		assign_border_pixel('-', t, x, fg);
		assign_border_pixel('-', d, x, fg);
	}
	// vertical lines
	for (uint8_t y = t; y <= d; y++) {
		assign_border_pixel('|', y, l, fg);
		assign_border_pixel('|', y, r, fg);
	}
	// a '+' for each corner
	assign_border_pixel('+', t, l, fg);
	assign_border_pixel('+', t, r, fg);
	assign_border_pixel('+', d, l, fg);
	assign_border_pixel('+', d, r, fg);
}

/**
 * @ pixel config
 * */
void GameboardRenderer::assign_border_pixel(char c, uint8_t y, uint8_t x, char fg) {
	scr->map[y][x] = c;
	scr->fgc[y][x] = fg;
	scr->bgc[y][x] = Color::Black;	// use bgc to trace path later
	scr->usg[y][x] = Renderer::UseBackground;
}

void GameboardRenderer::assign_core_pixel(uint8_t c, uint8_t y, uint8_t x) {
	static constexpr int ViableColors = 6;
	c--;

	char color = '1' + (c % ViableColors);	// [1:6]
	char letter = 'A' + c;
	if (letter > 'Z') {
		letter = letter - 'Z' - 1 + 'a';
		// avoid 'a' and 'A' having a same color
		color = '1' + ((c + 2) % ViableColors);
	}
	
	scr->map[y][x] = letter;
	scr->fgc[y][x] = color;
	scr->thk[y][x] = Color::Bold;
	scr->usg[y][x] = Renderer::UseThickness;
}
