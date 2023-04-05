
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
#include <ctime>
#include <string>
#include <random>
#include <fstream>
#include "hacking-param.h"
#include "hacking-template.h"
#include "account.h"
#include "game-operator.h"

/*
@ about this:
	import/export gamedata <-> template savefile
*/

struct HackingAPI {
public:
	static HackingSavefile import(std::string& path);
	static void write(std::string& path, Account& acc, GameOperator& opr);

	static void apply_mask(HackingSavefile& save);
	static void mask(char* str, char msk, int len);

	static HackingDate get_date();
};

#endif	// HACKING_API_H
