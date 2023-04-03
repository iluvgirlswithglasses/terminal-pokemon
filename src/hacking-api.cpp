
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Apr  3 15:08:49 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "hacking-api.h"

HackingSavefile HackingAPI::import(std::string& path) {
	// read
	HackingSavefile save;
	std::ifstream fi(path, std::ios::out | std::ios::binary);
	fi.read((char*) &save, sizeof(HackingSavefile));

	// decode
	mask(save.usrn, save.mask, HackingParam::UsrnLen);
	mask(save.pass, save.mask, HackingParam::PassLen);

	return save;
}

void HackingAPI::mask(char* str, char msk, int len) {
	for (int i = 0; i < len; i++) {
		if (!str[i]) return;
		str[i] ^= msk;
	}
}
