
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 15:02:04 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "lvl-info.h"

const int LvlInfo::DiffLvlCount[] = { 3, 3, 3, 3, 3, 3, 6, };

std::string LvlInfo::get_savefile(int dif, int lvl, Account& acc) {
	std::string ans = "sav/";
	ans += (char) ('0' + dif); ans += (char) ('0' + lvl);
	ans += '/';
	ans += acc.usrn; ans += ".bin";
	return ans;
}
