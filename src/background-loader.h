
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Sat Apr  1 19:01:38 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef BACKGROUND_LOADER_H
#define BACKGROUND_LOADER_H
// ------------------------------------------------------------

/*
@ about this:
	load a background file onto a grid 
	of the size declared in param.h 
*/

#include <cstring>
#include <fstream>
#include "param.h"

struct BackgroundLoader {
	static void load(const char* fname, char** container);
};

#endif	// BACKGROUND_LOADER_H
