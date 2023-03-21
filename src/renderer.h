
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Mar 21 08:45:07 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef RENDERER_H
#define RENDERER_H
// ------------------------------------------------------------

/*
@ about this:

*/

#include <cstdlib>
#include "param.h"
#include "color.h"

struct Renderer {
public:

	uint8_t h = Param::ScreenHeight, w = Param::ScreenWidth;

	char** map;	// screen grid
	char** fgc;	// foreground color for each cell in grid
	char** bgc;	// background color .....................
	char** thk;	// foreground thickness .................
	bool** usg;	// 0 --> use bg color, 1 --> use thickness

	Renderer();
	void render();	// render the current screen
	void clrscr();	// clear the screen

private:

};

#endif	// RENDERER_H
