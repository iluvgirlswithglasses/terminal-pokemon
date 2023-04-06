
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Thu Apr  6 13:21:19 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef HACKING_CONSOLE_H
#define HACKING_CONSOLE_H
// ------------------------------------------------------------

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include "input.h"
#include "account.h"
#include "hacking-api.h"

struct HackingConsole {
public:
	static void start(Account& acc);

private:
	static constexpr int OpenSucceed = 0, OpenFailed = 1, PermissionDenied = 2;

	static int read_file(Account& acc, std::string& url);
	static int hack_file(Account& acc, std::string& url);
};

#endif	// HACKING_CONSOLE_H