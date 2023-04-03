
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Sun Apr  2 21:51:01 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef FILE_FETCHER_H
#define FILE_FETCHER_H
// ------------------------------------------------------------

#include <cstdio>
#include <string>
#include "array.h"
#include "deque.h"

#if __linux__
#include <filesystem>
#elif _WIN32
#include <dirent.h>
#endif

struct FileFetcher {
public:
	static Array<std::string> ls(std::string d);
};

#endif	// FILE_FETCHER_H
