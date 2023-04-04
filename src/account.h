
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 09:31:10 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H
// ------------------------------------------------------------

#include <cstring>
#include <fstream>
#include "hacking-param.h"

struct Account {
	char usrn[HackingParam::UsrnLen];
	char pass[HackingParam::PassLen];

	static bool validate(Account& acc);	// check if the login credentials is correct
	static void save(Account& acc);		// save this account data to database
	static Account* list(int& len);		// list all accounts
};

#endif	// ACCOUNT_H
