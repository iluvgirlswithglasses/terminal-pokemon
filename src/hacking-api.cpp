
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
	if (!fi.is_open()) {
		save.usrn[0] = '\0';	// mark this as open failed
		return save;
	}
	fi.read((char*) &save, sizeof(HackingSavefile));

	// decode
	mask(save.usrn, save.mask, HackingParam::UsrnLen);
	mask(save.pass, save.mask, HackingParam::PassLen);
	for (int i = 0; i < HackingParam::PathLen; i++) {
		mask(save.state[i].board, save.mask, HackingParam::GameLen);
		mask(save.state[i].bgUrl, save.mask, HackingParam::PathLen);
	}

	return save;
}

void HackingAPI::mask(char* str, char msk, int len) {
	for (int i = 0; i < len; i++) {
		if (!str[i]) return;
		str[i] ^= msk;
	}
}
