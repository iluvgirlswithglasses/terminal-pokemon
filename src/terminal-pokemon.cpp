
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
#include <cstdint>
#include "renderer.h"
#include "gameboard.h"
#include "gameboard-renderer.h"
#include "gameboard-logic-easy.h"
#include "gameboard-logic-normal.h"

int h, w;
uint8_t** data;

Gameboard read() {
    scanf("%d%d", &h, &w);
    data = new uint8_t*[h];
    for (int i = 0; i < h; i++) {
        data[i] = new uint8_t[w];
        for (int j = 0; j < w; j++) scanf("%d", &data[i][j]);
    }
    return Gameboard(h, w, data);
}

void prf_board(Gameboard &board) {
    printf("gameboard:\n");
    for (int y = 0; y < board.h; y++) {
        for (int x = 0; x < board.w; x++) {
            if (board.map[y][x]) printf("%d ", board.map[y][x]);
            else printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

void check(GameboardLogic &logic, int y0, int x0, int y1, int x1) {
    if (logic.validate(y0, x0, y1, x1)) {
        printf("ok\n");
        Deque<uint16_t> path = logic.get_path(y0, x0, y1, x1);
        while (path.count()) {
            printf("(%d, %d) ", path.front()>>8, path.front()&GameboardLogic::MSK8);
            path.pop_front();
        }
        printf("\n");
    } else {
        printf("not ok\n");
    }
}

int main() {
    Gameboard board = read();
    prf_board(board);
    
    GameboardLogicNormal logicN(board.h, board.w, board.map);
    GameboardLogicEasy   logicE(board.h, board.w, board.map);
    
    Renderer rdr;
    GameboardRenderer gameboardRdr(board.map, &rdr, board.h, board.w, 2, 0);
    gameboardRdr.burn();
    rdr.render();

    int dummy; scanf("%d", dummy);
    rdr.clrscr();
	return 0;
}
