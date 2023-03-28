
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
#include <winuser.h>
#include "renderer.h"

struct WindowsConsole {
public:
	// init the terminal
	static void init() {
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		// hide the cursor
		CONSOLE_CURSOR_INFO cursor;
		GetConsoleCursorInfo(out, &cursor);
		cursor.bVisible = false;
		SetConsoleCursorInfo(out, &cursor);

		// fix the buffer size (even this can't help the terrible performance)
		COORD bufSize = { Param::ScreenWidth, Param::ScreenHeight };
		SetConsoleScreenBufferSize(out, bufSize);

		// set window size
		SMALL_RECT wndSz;
		wndSz.Top = 0;
		wndSz.Left = 0;
		wndSz.Bottom = Param::ScreenHeight;
		wndSz.Right = Param::ScreenWidth;
		SetConsoleWindowInfo(out, true, &wndSz);
	}

	// replace a single pixel to the console
	// without re-rendering the whole frame
	static void plot_pixel(Renderer* rdr, uint8_t y, uint8_t x) {
		set_cursor(y, x);
		if (rdr->usg[y][x] == Renderer::UseBackground) 
			Color::setfb(rdr->fgc[y][x], rdr->bgc[y][x]);
		else 
			Color::setft(rdr->fgc[y][x], rdr->thk[y][x]);
		putchar(rdr->map[y][x]);
	}

	// move the cursor to a cell
	// kinda unmanageable, please avoid using
	static void set_cursor(uint8_t y, uint8_t x) {
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD cursor = { x, y };	// COORD(x, y)
		SetConsoleCursorPosition(console, cursor);
	}
};

#endif	// _WIN32
#endif	// WINDOWS_CONSOLE_H
