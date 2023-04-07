
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Fri Apr  7 17:35:46 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "gameboard-renderer.h"

GameboardRenderer::GameboardRenderer(Gameboard* _board, Renderer* _rdr) {
	board = _board;
	rdr = _rdr;

	row = SaveLoader::H;
	col = SaveLoader::W;
	top = 0;
	lft = 0;
}

GameboardRenderer::~GameboardRenderer() {
	if (map != nullptr) {
		for (int y = 0; y < row; y++) delete[] map[y];
		delete[] map;
	}
}

/**
 * @ utils
 * */
void GameboardRenderer::burn() {
	// load the gameboard first
	if (map != nullptr) {
		for (int y = 0; y < row; y++) delete[] map[y];
		delete[] map;
	}
	map = board->to_array();

	// the rest goes like the main game
	reset();
	for (int y = 0; y < row; y++)
		for (int x = 0; x < col; x++)
			if (map[y][x] != Gameboard::EmptyCell) draw_cell(y, x);
}

void GameboardRenderer::reset() {
	int t = get_ry(0), d = get_ry(row), l = get_rx(0), r = get_rx(col);
	for (int y = t; y <= d; y++) { 		// [t, d], not [t, d) because border
		for (int x = l; x <= r; x++) {	// same here
			rdr->map[y][x] = ' ';
			rdr->bgc[y][x] = Renderer::Black;
			rdr->fgc[y][x] = Renderer::White;
		}
	}
}

/**
 * @ cells rendering
 * */
void GameboardRenderer::draw_cell(int y, int x) {
	int t = get_ry(y), d = get_ry(y+1), l = get_rx(x), r = get_rx(x+1);
	// draw border
	draw_border(y, x, Renderer::White);
	// then assign the tile
	assign_core_pixel(map[y][x], t + MidY, l + MidX);
}

void GameboardRenderer::draw_border(int y, int x, char fg) {
	int t = get_ry(y), d = get_ry(y+1), l = get_rx(x), r = get_rx(x+1);
	// horizontal lines
	for (int x = l; x <= r; x++) {
		assign_border_pixel('-', t, x, fg);
		assign_border_pixel('-', d, x, fg);
	}
	// vertical lines
	for (int y = t; y <= d; y++) {
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
void GameboardRenderer::assign_border_pixel(char c, int y, int x, char fg) {
	rdr->map[y][x] = c;
	rdr->fgc[y][x] = fg;
	rdr->bgc[y][x] = Renderer::Black;
}

void GameboardRenderer::assign_core_pixel(int c, int y, int x) {
	static constexpr int ViableColors = 6;
	
	char color = '1' + (c % ViableColors);	// [1:6]
	rdr->map[y][x] = c;
	rdr->fgc[y][x] = color;
}
