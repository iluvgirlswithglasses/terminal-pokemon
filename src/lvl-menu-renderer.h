
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 15:22:59 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef LVL_MENU_RENDERER_H
#define LVL_MENU_RENDERER_H
// ------------------------------------------------------------

/*
@ about this:
	render a level menu for the user to select
	returns in format (dif << 8 | lvl)

	this object only render a part of the screen
	you may use the other spaces however you want
*/

#include <cstdint>
#include <cstring>
#include "lvl-info.h"
#include "renderer.h"
#include "input.h"

struct LvlMenuRenderer {
	static constexpr uint8_t TabSize = 4;

	uint8_t top, lft;		// top & left margin
	uint8_t h, w;			// the size of the menu
	Renderer* rdr;			// screen renderer

	// locY[i] = the y-axis of where item `i` is displayed on the screen
	uint8_t locY[LvlInfo::LvlCount];

	// the difficulty of the `i` item
	int itemDif[LvlInfo::LvlCount];
	int itemLvl[LvlInfo::LvlCount];

	LvlMenuRenderer(Renderer* rdr, uint8_t t, uint8_t l, uint8_t h, uint8_t w);
	void start(int& dif, int& lvl);

	void select(int i);		// select an item
	void deselect(int i);	// deselect an item
};

#endif	// LVL_MENU_RENDERER_H
