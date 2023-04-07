
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

#include <cstdio>
#include <cstdlib>

struct Renderer {
	static constexpr char
		Black  = '9',	// not true black '0', but default terminal color
		Red    = '1',
		Green  = '2',
		Yellow = '3',
		Blue   = '4',
		Purple = '5',
		Cyan   = '6',
		White  = '7';

	static constexpr int H = 12 + 1, W = 24 + 1;

	char** map;	// screen grid
	char** fgc;	// foreground color for each cell in grid
	char** bgc;	// background color .....................

	Renderer();
	void render();	// render the current screen
	void clrscr();	// clear the screen
	void clrmap();	// clear all data
};

#endif	// RENDERER_H
