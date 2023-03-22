
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Mar 21 20:33:28 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "gameboard-logic-easy.h"

/**
 * @ initializer & deconstructor
 * */
GameboardLogicEasy::GameboardLogicEasy(uint8_t _h, uint8_t _w, uint8_t** _map) {
	h = _h;
	w = _w;
	map = _map;

	vst = new uint8_t*[h];
	for (int y = 0; y < h; y++)
		vst[y] = new uint8_t[w];

	trace = new uint16_t*[h];
	for (int y = 0; y < h; y++)
		trace[y] = new uint16_t[w];
}

GameboardLogicEasy::~GameboardLogicEasy() {
	for (int y = 0; y < h; y++) {
		delete[] vst[y];
		delete[] trace[y];
	}
	delete[] vst;
	delete[] trace;
}

/**
 * @ tracing DFS
 * */
Deque<uint16_t> GameboardLogicEasy::get_path(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
	Deque<uint16_t> ans;
	ans.push_front(key(y1, x1));
	traceDFS(ans, y0, x0, y1, x1);
	return ans;
}

void GameboardLogicEasy::traceDFS(Deque<uint16_t> &q, uint8_t dy, uint8_t dx, uint8_t y, uint8_t x) {
	uint16_t nxt = trace[y][x];
	q.push_front(nxt);
	uint8_t ny = nxt>>8, nx = nxt&MSK8;
	if (ny == dy && nx == dx) return;
	traceDFS(q, dy, dx, ny, nx);
}

/**
 * @ BFS
 * */
bool GameboardLogicEasy::validate(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
	return BFS(y0, x0, true, y1, x1);
}

uint32_t GameboardLogicEasy::suggest() {
	for (int y = 1; y < h-1; y++) for (int x = 1; x < w-1; x++) if (map[y][x]) {
		uint32_t self  = (y<<8|x)<<16;
		uint16_t other = BFS(y, x);
		if (other != 0) return self|other;
	}
	return 0; // the map is corrupted
}

void GameboardLogicEasy::reset_vst() {
	for (int y = 0; y < h; y++)
		memset(vst[y], 0, sizeof(vst[y][0]) * w);
}

uint16_t GameboardLogicEasy::BFS(uint8_t y0, uint8_t x0, bool fixed, uint8_t y1, uint8_t x1) {
	// move rules
	static constexpr int 
		RY[RC] = { -1, 0, 1, 0, },	// adj `y` cells {t, l, d, r}
		RX[RC] = { 0, -1, 0, 1, };	// adj `x` cells {t, l, d, r}

	// even the type is different
	if (fixed && map[y0][x0] != map[y1][x1]) return 0;

	// set up
	reset_vst();
	Deque<uint16_t> q;
	q.push_back(key(y0, x0));
	vst[y0][x0] = true;

	while (q.count()) {
		uint8_t y = q.front()>>8, x = q.front()&MSK8;
		q.pop_front();
		for (int t = 0; t < RC; t++) {
			uint16_t ans = 0;
			int nxtY32 = static_cast<int>(y) + RY[t], 
			    nxtX32 = static_cast<int>(x) + RX[t];
			if (0 < nxtY32 || 0 < nxtX32 || nxtY32 >= h || nxtX32 >= w) continue;
			uint8_t nxtY = nxtY32, nxtX = nxtX32;
			if (vst[nxtY][nxtX]) continue;

			// found an answer
			if (fixed) {
				if (nxtY == y1 && nxtX == x1) ans = key(nxtY, nxtX);
			} else {
				if (map[nxtY][nxtX] == map[y0][x0]) ans = key(nxtY, nxtX);
			}

			// trace
			vst[nxtY][nxtX] = true;
			trace[nxtY][nxtX] = key(y0, x0);
			if (ans) return ans;

			// move to this cell
			if (map[nxtY][nxtX]) continue;
			q.push_back(key(nxtY, nxtX));
		}
	}

	return 0;
}
