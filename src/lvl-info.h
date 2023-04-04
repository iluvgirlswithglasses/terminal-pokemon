
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 14:55:45 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef LVL_INFO_H
#define LVL_INFO_H
// ------------------------------------------------------------

#include <string>
#include "account.h"

struct LvlInfo {
	static const int DiffCount = 7;
	static const int LvlCount = 24;
	static const int DiffLvlCount[DiffCount];
	static const std::string DiffName[DiffCount];

	static std::string get_savefile(int dif, int lvl, Account& acc);
};

#endif	// LVL_INFO_H
