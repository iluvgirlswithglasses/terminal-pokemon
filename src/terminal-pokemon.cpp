
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
#include "background-loader.h"

int main(int argc, const char* argv[]) {
	/*
#if _WIN32	// something to deal with windows' terrible performance
	WindowsConsole::init();
#endif

	int diff, lvl;
	scanf("%d%d", &diff, &lvl);

	// operate the game
	GameOperator game(diff, lvl);
	if (game.start()) 
		printf("you won --tmp\n");
	else
		printf("bruh --tmp\n");
	*/
	char** map = new char*[Param::ScreenHeight];
	for (int y = 0; y < Param::ScreenHeight; y++)
		map[y] = new char[Param::ScreenWidth];
	BackgroundLoader::load("bgr/airstrike.txt", map);
	for (int y = 0; y < Param::ScreenHeight; y++) {
		for (int x = 0; x < Param::ScreenWidth; x++)
			printf("%c", map[y][x]);
		printf("\n");
	}
	return 0;
}
