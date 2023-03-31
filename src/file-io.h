
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Fri Mar 31 17:29:13 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef FILE_IO_H
#define FILE_IO_H
// ------------------------------------------------------------

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

struct FileIO {
public:
	static bool read_lvl(char* fname, uint8_t** map, uint8_t& h, uint8_t& w);
};

#endif	// FILE_IO_H
