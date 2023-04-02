
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Mar 20 08:08:34 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include <cstdio>
#include "game-operator.h"

int main(int argc, const char* argv[]) {

#if _WIN32	// something to deal with windows' terrible performance
	WindowsConsole::init();
#endif

	int diff, lvl, bgr;
	scanf("%d%d%d", &diff, &lvl, &bgr);

	// operate the game
	GameOperator game(diff, lvl, bgr);
	if (game.start()) 
		printf("you won --tmp\n");
	else
		printf("bruh --tmp\n");
	return 0;
}
