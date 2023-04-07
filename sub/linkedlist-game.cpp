
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Thu Apr  6 17:49:19 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include <iostream>
#include <cstdio>
#include "operator.h"
#include "renderer.h"

#if _WIN32		// ----------------------------------
#include <windows.h>
void hide_cursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(out, &cursor);
	cursor.bVisible = false;
	SetConsoleCursorInfo(out, &cursor);
}
#elif __linux__	// ----------------------------------
void hide_cursor() {}
#endif			// ----------------------------------

char ask_gamemode() {
	printf("choose sliding mode:\n");
	printf("(type 't' for top, 'l' for left, 'd' for down, or 'r' for right)\n");
	printf("(invalid input will be considered as 'l')\n");
	printf(">>> ");

	char ans;
	std::cin >> ans;
	if (ans != 't' && ans != 'd' && ans != 'r') ans = 'l';
	return ans;
}

int main() {
	hide_cursor();
	Renderer* rdr = new Renderer();

	char ori = ask_gamemode();
	Operator game(rdr, ori);
	bool status = game.start();

	if (status) 
		printf("you won! press any key to exist\n");
	else 
		printf("you lost! press any key to exist\n");

	Input::wait_keypress();
	return 0;
}
