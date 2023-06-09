
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Mar 21 19:09:32 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "gameboard-logic-normal.h"

/**
 * @ initializer & deconstructor
 * */
GameboardLogicNormal::GameboardLogicNormal(uint8_t _h, uint8_t _w, uint8_t** _map) {
	h = _h;
	w = _w;
	map = _map;

	// vst[t][y, x] == d
	// --> cell (y, x) was visited via a `t` move with `d-1` turns remaining
	//     if d == 0, its mean that the cell was not visited
	vst = new uint8_t**[RC];
	for (int t = 0; t < RC; t++) {
		vst[t] = new uint8_t*[h];			// 2d array
		for (int y = 0; y < h; y++)
			vst[t][y] = new uint8_t[w];	// 1d array
	}
	// trace[t][y, x] == (pt<<16) | (py<<8) | px
	//                   where `p` means parent
	trace = new uint32_t**[RC];
	for (int t = 0; t < RC; t++) {
		trace[t] = new uint32_t*[h];
		for (int y = 0; y < h; y++)
			trace[t][y] = new uint32_t[w];
	}
}

GameboardLogicNormal::~GameboardLogicNormal() {
	for (int t = 0; t < RC; t++) {
		for (int y = 0; y < h; y++) {
			delete[] vst[t][y];
			delete[] trace[t][y];
		}
		delete[] vst[t];
		delete[] trace[t];
	}
	delete[] vst;
	delete[] trace;
}

/**
 * @ Tracing DFS
 * */
Deque<uint16_t> GameboardLogicNormal::get_path(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
	Deque<uint16_t> ans;
	uint8_t move = RC;
	for (int t = 0; t < RC; t++) if (vst[t][y1][x1]) {
		move = t;
		break;
	}
	if (move == RC) return ans;
	ans.push_front(y1<<8|x1);
	traceDFS(ans, y0, x0, y1, x1, move);
	return ans;
}

void GameboardLogicNormal::traceDFS(Deque<uint16_t> &q, uint8_t dy, uint8_t dx, uint8_t y, uint8_t x, uint8_t d) {
	uint32_t nxt = trace[d][y][x];
	uint8_t nxtX = nxt       & MSK8,
	        nxtY = (nxt>>8)  & MSK8,
	        nxtD = (nxt>>16) & MSK8;
	q.push_front(nxtY<<8|nxtX);
	if (nxtY == dy && nxtX == dx) return;
	traceDFS(q, dy, dx, nxtY, nxtX, nxtD);
}

/**
 * @ BFS
 * */
bool GameboardLogicNormal::validate(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
	return BFS(y0, x0, true, y1, x1);
}

uint32_t GameboardLogicNormal::suggest() {
	for (int y = 1; y < h-1; y++) for (int x = 1; x < w-1; x++) if (map[y][x]) {
		uint32_t self  = (y<<8|x)<<16;
		uint16_t other = BFS(y, x);
		if (other != 0) return self|other;
	}
	return 0; // the map is corrupted
}

/**
 * @ BFS Utils
 * */
void GameboardLogicNormal::reset_vst() {
	// set all vst's content to 0
	for (int t = 0; t < RC; t++)
		for (int y = 0; y < h; y++)
			memset(vst[t][y], 0, sizeof(vst[t][y][0]) * w);
}

uint16_t GameboardLogicNormal::BFS(uint8_t y0, uint8_t x0, bool fixed, uint8_t y1, uint8_t x1) {
	// even the type is different
	if (fixed && map[y0][x0] != map[y1][x1]) return 0;

	// set up
	reset_vst();

	Deque<uint8_t> qy;	// y deque
	Deque<uint8_t> qx;	// x deque
	Deque<uint8_t> qt;	// the last turn taken
	Deque<uint8_t> qd;	// the number of turns remaining (depth+1)

	qy.push_back(y0);
	qx.push_back(x0);
	qt.push_back(RC);
	qd.push_back(MaxDepth+1);

	for (int t = 0; t < RC; t++)
		vst[t][y0][x0] = MaxDepth + 10;	// never to visit this cell again

	while (qy.count()) {
		uint8_t y = qy.pop_front(), 
		        x = qx.pop_front(), 
		        t = qt.pop_front(), 
		        d = qd.pop_front();
		for (int move = 0; move < RC; move++) {
			// if `ans != 0` in the end of this iteration
			// its mean that we found an answer
			uint16_t ans = 0;

			// check if index out of bound
			int nxtY32 = RY[move] + static_cast<int>(y),
			    nxtX32 = RX[move] + static_cast<int>(x);
			if (nxtY32 >= h || nxtX32 >= w || nxtY32 < 0 || nxtX32 < 0) continue;
			uint8_t nxtY = nxtY32, nxtX = nxtX32;

			// check if out of turning points (maximum = 2)
			uint8_t nxtD = d;
			if (t != RC && move != t) nxtD--;
			if (nxtD == 0) continue;

			// this cell is already visited via a path with less depth
			if (vst[move][nxtY][nxtX] >= nxtD) continue;

			// check if found the destination
			if (fixed) {
				if (nxtY == y1 && nxtX == x1) ans = key(nxtY, nxtX);
			} else {
				if (map[nxtY][nxtX] == map[y0][x0]) ans = key(nxtY, nxtX);
			}

			// trace
			vst[move][nxtY][nxtX] = nxtD;
			trace[move][nxtY][nxtX] = (static_cast<uint32_t>(t)<<16) | (static_cast<uint32_t>(y)<<8) | (static_cast<uint32_t>(x));

			if (ans != 0) return ans;	// only returns after tracing

			// not an empty cell --> cant move here
			if (map[nxtY][nxtX]) continue;

			// move to next cell
			qy.push_back(nxtY);
			qx.push_back(nxtX);
			qt.push_back(move);
			qd.push_back(nxtD);
		}
	}

	return 0;
}
