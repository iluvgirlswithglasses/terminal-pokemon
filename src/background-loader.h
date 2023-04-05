
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

#include <random>
#include <fstream>
#include <string>
#include "param.h"
#include "file-fetcher.h"

struct BackgroundLoader {
public:
	static const std::string BackgroundDirectory;

	static void load(std::string& fname, char** container);
	static void load(int id, char** container);
	static std::string rand_load(char** container);	// randomized
};

#endif	// BACKGROUND_LOADER_H
