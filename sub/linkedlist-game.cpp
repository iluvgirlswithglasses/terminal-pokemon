
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

#include <cstdio>
#include "save-loader.h"
#include "gameboard.h"

int main() {
	SaveLoader save;
	char** map = save.get_map();
	Gameboard board(map, SaveLoader::H, SaveLoader::W);
	SaveLoader::del_map(map);

	map = board.to_array();

	for (int y = 0; y < SaveLoader::H; y++) {
		for (int x = 0; x < SaveLoader::W; x++) 
			printf("%c ", map[y][x]);
		printf("\n");
	}
	return 0;
}
