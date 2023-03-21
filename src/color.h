
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Mar 20 10:47:54 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef COLOR_H
#define COLOR_H
// ------------------------------------------------------------

#include <cstdio>

struct Color {
public:
	static constexpr char
		Black  = '0',
		Red    = '1',
		Green  = '2',
		Yellow = '3',
		Blue   = '4',
		Purple = '5',
		Cyan   = '6',
		White  = '7';

	static constexpr char
		Regular = '0',
		Bold = '1';

	// set foreground & thickness
	inline static void setft(char fg, char th) { printf("\033[%c;3%cm", th, fg); }
	// set foreground & background
	inline static void setfb(char fg, char bg) { printf("\033[4%c;3%cm", bg, fg); }
	// reset
	inline static void reset() { printf("\033[0m"); }
};

#endif // COLOR_H
