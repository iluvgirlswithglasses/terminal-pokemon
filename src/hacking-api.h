
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Apr  3 15:03:32 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef HACKING_API_H
#define HACKING_API_H
// ------------------------------------------------------------

#include <cstring>
#include <string>
#include <fstream>
#include "hacking-param.h"
#include "hacking-template.h"

/*
@ about this:
	import/export gamedata <-> template savefile
*/

struct HackingAPI {
public:
	static HackingSavefile import(std::string& path);
	static void mask(char* str, char msk, int len);
};

#endif	// HACKING_API_H
