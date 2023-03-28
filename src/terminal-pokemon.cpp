
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

int main() {
	GameOperator game;
	if (game.start(GameOperator::DiffHard)) 
		printf("you won --tmp\n");
	else
		printf("bruh --tmp\n");
	return 0;
}
