
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 13:04:18 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "scene-login.h"

Account SceneLogin::start() {
	Account acc;
	int status;

	printf("please login first.\n");
	printf("if you login via an unknown username,\n");
	printf("the game will automatically register that account for you.\n\n");

	do {
		printf("username: ");
		scanf("%s", acc.usrn);
		printf("password: ");
		getpwd(acc);

		status = Account::validate(acc);
		switch (status) {
		case Account::ConstraintsNotMet:
			Color::setft(Color::Red, Color::Regular);
			printf("ERROR: password and username must have the length of 4 or more\n");
			Color::reset();
			break;
		case Account::WrongPassword:
			Color::setft(Color::Red, Color::Regular);
			printf("ERROR: wrong password\n");
			Color::reset();
			break;
		case Account::AccountDoesNotExist:
			Color::setft(Color::Green, Color::Regular);
			printf("SUCCEED: created a new account with this username and password\n");
			Color::reset();
			break;
		case Account::ValidCredentials:
			Color::setft(Color::Green, Color::Regular);
			printf("SUCCEED: login successfully!\n");
			Color::reset();
			break;
		}
	} while (status != Account::AccountDoesNotExist && status != Account::ValidCredentials);

	// a new account is registered
	if (status == Account::AccountDoesNotExist) Account::save(acc);

	printf("press any key to continue...\n");
	Input::wait_keypress();

	return acc;
}

#if __linux__	// --------------------------------------------

void SceneLogin::getpwd(Account& acc) {
	scanf("%s", acc.pass);
}

#elif _WIN32	// --------------------------------------------

#include <windows.h>
void SceneLogin::getpwd(Account& acc) {
	int len = 0;
	char c = _getch();
	while (c != 13) {
		acc.pass[len++] = c;
		printf("*");
		c = _getch();
	}
	printf("\n");
	acc.pass[len] = '\0';	// manually end the string here
}

#endif			// --------------------------------------------
