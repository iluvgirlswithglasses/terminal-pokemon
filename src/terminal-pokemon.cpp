
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
#include <cstring>

#include "color.h"
#include "param.h"
#include "gameboard.cpp"

int h, w;
uint8_t** data;

GameBoard read() {
    scanf("%d%d", &h, &w);
    data = new uint8_t*[h];
    for (int i = 0; i < h; i++) {
        data[i] = new uint8_t[w];
        for (int j = 0; j < w; j++) scanf("%d", &data[i][j]);
    }
    return GameBoard(h, w, data);
}

int main() {
    GameBoard board = read();
	return 0;
}
