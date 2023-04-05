
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

GameboardRenderer::GameboardRenderer(uint8_t** _map, std::string& bgUrl, Renderer* _scr, uint8_t _row, uint8_t _col, uint8_t _top, uint8_t _lft) {
	map = _map;
	scr = _scr;
	row = _row;
	col = _col;
	top = _top;
	lft = _lft;

	// load background
	bgr = new char*[Param::ScreenHeight];
	for (int y = 0; y < Param::ScreenHeight; y++)
		bgr[y] = new char[Param::ScreenWidth];
	bgUrl = BackgroundLoader::rand_load(bgr);

	// burn the background to the renderer
	for (int y = 0; y < Param::ScreenHeight; y++)
		for (int x = 0; x < Param::ScreenWidth; x++)
			assign_border_pixel(bgr[y][x], y, x, Color::White);
}

void GameboardRenderer::burn() {
	reset();
	for (uint8_t y = 0; y < row; y++)
		for (uint8_t x = 0; x < col; x++)
			if (map[y][x] > 0) draw_cell(y, x);
}

void GameboardRenderer::reset() {
	uint8_t t = get_ry(0), d = get_ry(row), l = get_rx(0), r = get_rx(col);
	for (uint8_t y = t; y <= d; y++) { 		// [t, d], not [t, d) because border
		for (uint8_t x = l; x <= r; x++) {	// same here
			scr->map[y][x] = bgr[y][x];
			scr->fgc[y][x] = Color::White;
			scr->bgc[y][x] = Color::Black;
			scr->thk[y][x] = Color::Regular;
			scr->usg[y][x] = Renderer::UseBackground;
		}	
	}
}

/**
 * @ cells rendering
 * */
void GameboardRenderer::draw_cell(uint8_t y, uint8_t x) {
	uint8_t t = get_ry(y), d = get_ry(y+1), l = get_rx(x), r = get_rx(x+1);
	// clear background
	for (uint8_t y = t; y <= d; y++)
		for (uint8_t x = l; x <= r; x++)
			assign_border_pixel(' ', y, x, Color::White);
	// draw border
	draw_border(y, x, Color::White);
	// then assign the tile
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

void GameboardRenderer::draw_path(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1, char bg) {
	y0 = get_ry(y0) + MidY;
	x0 = get_rx(x0) + MidX;
	y1 = get_ry(y1) + MidY;
	x1 = get_rx(x1) + MidX;

	auto min = [=](uint8_t a, uint8_t b) { return a < b ? a : b; };
	auto max = [=](uint8_t a, uint8_t b) { return a > b ? a : b; };

	if (y0 == y1) {
		for (uint8_t x = min(x0, x1); x <= max(x0, x1); x++)
			if (scr->usg[y0][x] == Renderer::UseBackground)
				scr->bgc[y0][x] = bg;
	} else if (x0 == x1) {
		for (uint8_t y = min(y0, y1); y <= max(y0, y1); y++)
			if (scr->usg[y][x0] == Renderer::UseBackground)
				scr->bgc[y][x0] = bg;
	}

#if _WIN32	// ------------------------------------------------------------------------
	/** the design flaw of this block is mentioned at @FLAW in `game-operator.cpp` */
	if (y0 == y1) {
		for (uint8_t x = min(x0, x1); x <= max(x0, x1); x++)
			if (scr->usg[y0][x] == Renderer::UseBackground)
				WindowsConsole::plot_pixel(scr, y0, x);
	} else if (x0 == x1) {
		for (uint8_t y = min(y0, y1); y <= max(y0, y1); y++)
			if (scr->usg[y][x0] == Renderer::UseBackground)
				WindowsConsole::plot_pixel(scr, y, x0);
	}
	WindowsConsole::reset_cursor();
#endif		// _WIN32 -----------------------------------------------------------------
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

/**
 * @ windows
 * */
#if _WIN32	// ----------------------------------------------------------------
// this method does not burn nor modify anything
// it only calls WindowsConsole
void GameboardRenderer::direct_render_cell(uint8_t y, uint8_t x) {
	uint8_t t = get_ry(y), d = get_ry(y+1), l = get_rx(x), r = get_rx(x+1);
	for (uint8_t y = t; y <= d; y++)
		for (uint8_t x = l; x <= r; x++)
			WindowsConsole::plot_pixel(scr, y, x);
	WindowsConsole::reset_cursor();
}
#endif		// ----------------------------------------------------------------
