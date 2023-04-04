
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
public:
	char usrn[HackingParam::UsrnLen];
	char pass[HackingParam::PassLen];

	static constexpr int
		AccountDoesNotExist = 0,
		WrongPassword = 1,
		ValidCredentials = 2,
		ConstraintsNotMet = 3;

	static bool check_constraints(Account& acc);
	static int validate(Account& acc);	// check if the login credentials is correct
	static void save(Account& acc);		// save this account data to database
	static Account* list(int& len);		// list all accounts
};

#endif	// ACCOUNT_H
