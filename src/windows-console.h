
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Mar 27 16:16:43 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef WINDOWS_CONSOLE_H
#define WINDOWS_CONSOLE_H
// ------------------------------------------------------------
/*
@ about this:
	windows terminal is so bad 
	i had to write a whole module to optimize it manually
*/

#if _WIN32

#include <windows.h>
#include "renderer.h"

struct WindowsConsole {
public:
	static void PlotPixel(Renderer* rdr, uint8_t y, uint8_t x) {
		auto console = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD cursor = { x, y };	// COORD(x, y)
		::SetConsoleCursorPosition(console, cursor);
		if (rdr->usg[y][x] == Renderer::UseBackground) 
			Color::setfb(rdr->fgc[y][x], rdr->bgc[y][x]);
		else 
			Color::setft(rdr->fgc[y][x], rdr->thk[y][x]);
		putchar(rdr->map[y][x]);
	}
};

#endif	// _WIN32
#endif	// WINDOWS_CONSOLE_H
