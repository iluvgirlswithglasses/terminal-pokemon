
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

	inline static void set(char color, char bold) { printf("\033[%c;3%cm", bold, color); }
	inline static void reset() { printf("\033[0m"); }
};
