
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
const std::string LvlInfo::DiffName[] = {
	"Easy - Match in every patterns",
	"Normal - Match in patterns I L U Z",
	"Sliding Top - Normal rules with tiles sliding up",
	"Sliding Left - Normal rules with tiles sliding left",
	"Sliding Down - Normal rules with tiles sliding down",
	"Sliding Right - Normal rules with tiles sliding right",
	"Naughty Tiles - Normal rules with tiles sometimes move",
};

std::string LvlInfo::get_savefile(int dif, int lvl, Account& acc) {
	std::string ans = "sav/";
	ans += (char) ('0' + dif); ans += (char) ('0' + lvl);
	ans += '/';
	ans += acc.usrn; ans += ".bin";
	return ans;
}
