
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
#include <cstring>
#include "color.h"
#include "background-loader.h"
#include "renderer.h"

#if _WIN32
#include "windows-console.h"
#endif	// _WIN32

struct GameboardRenderer {
public:
	uint8_t** map;			// the gameboard
	char**    bgr;			// the background (has the same size as the screen)
	Renderer* scr;			// the screen renderer
	uint8_t   row, col;		// the size of the gameboard
	uint8_t   top, lft;		// where the gameboard is projected on the screen

	GameboardRenderer(uint8_t** map, const char* bgr, Renderer* scr, uint8_t row, uint8_t col, uint8_t top, uint8_t lft);
	void burn();			// burns the gameboard into the screen grid

	// change the color of some cells
	// `burn()` overrides this method's effect
	void draw_border(uint8_t y, uint8_t x, char fg);

	// draw a path between 2 points
	// `burn()` overrides this method's effect
	void draw_path(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1, char bg);

#if _WIN32	// ----------------------------------------------------------------
	/*
	somethings to boost windows' terrible performance 
	these methods burns to Renderer & then directly renders via WindowsConsole

	these method DOES NOT use Renderer::render() nor modify the gameboard
	which still follows the overall rules of this struct to some degree
	*/
	// usage: call this to render just a cell and not the whole scene
	void direct_render_cell(uint8_t y, uint8_t x);
#endif		// _WIN32 ---------------------------------------------------------

private:
	static constexpr uint8_t CellHeight = 4, CellWidth = 8;	// must be even
	static constexpr uint8_t MidY = CellHeight>>1, MidX = CellWidth>>1;

	void reset();							// reset the screen
	void draw_cell(uint8_t y, uint8_t x);	// draws tile map[y, x]

	uint8_t get_ry(uint8_t y) { return top + CellHeight * y; }
	uint8_t get_rx(uint8_t x) { return lft + CellWidth * x; }

	// pixel configures
	void assign_border_pixel(char c, uint8_t y, uint8_t x, char fg);
	void assign_core_pixel(uint8_t c, uint8_t y, uint8_t x);
};

#endif	// GAMEBOARD_RENDERER_H
