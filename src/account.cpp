
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 09:39:32 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "account.h"

bool Account::validate(Account& acc) {
	int len = 0;
	Account* arr = list(len);
	for (int i = 0; i < len; i++) {
		if (strcmp(arr[i].usrn, acc.usrn) == 0)
			return strcmp(arr[i].pass, acc.pass) == 0;
	}
	delete[] arr;
	return false;
}

void Account::save(Account& acc) {
	int len = 0;
	Account* arr = list(len);
	len++;

	std::ofstream fo("sav/usrdata.bin", std::ios::in | std::ios::binary);
	fo.write((char*) &len, sizeof(len));
	for (int i = 0; i < len-1; i++)
		fo.write((char*) &arr[i], sizeof(Account));
	fo.write((char*) &acc, sizeof(Account));

	fo.close();
	delete[] arr;
}

Account* Account::list(int& len) {
	std::ifstream fi("sav/usrdata.bin", std::ios::in | std::ios::binary);
	if (fi.is_open()) {
		fi.read(reinterpret_cast<char*>(&len), sizeof(len));
		Account* ans = new Account[len];
		for (int i = 0; i < len; i++)
			fi.read((char*) &ans[i], sizeof(Account));
		fi.close();
		return ans;
	}
	len = 0;
	return nullptr;
}
