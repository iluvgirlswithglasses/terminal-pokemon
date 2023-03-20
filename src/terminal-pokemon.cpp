
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

void prf_board(GameBoard &board) {
    for (int y = 0; y < board.h; y++) {
        for (int x = 0; x < board.w; x++)
            printf("%d ", board.map[y][x]);
        printf("\n");
    }
}

int main() {
    GameBoard board = read();
    prf_board(board);
    while (true) {
        int y0, x0, y1, x1;
        scanf("%d %d %d %d", &y0, &x0, &y1, &x1);
        if (board.validate(y0, x0, y1, x1))
            printf("ok\n");
        else
            printf("not ok\n");
    }
	return 0;
}
