
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Mar 20 10:35:38 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef PARAM_H
#define PARAM_H
// ------------------------------------------------------------

#include <cstdint>

struct Param {
public:
	// screen size, measured in characters
	static constexpr uint8_t ScreenHeight = 30;
	static constexpr uint8_t ScreenWidth  = 100;
};

#endif	// PARAM_H
