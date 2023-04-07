
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Fri Apr  7 11:13:49 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "logic.h"

const int Logic::RY[] = { -1, 0, +1, 0 };	// tldr
const int Logic::RX[] = { 0, -1, 0, +1 };	// tldr

Logic::Logic(Gameboard* _board) {
	board = _board;
	h = board->h;
	w = board->w;

	// vst[t][y, x] == d
	// --> cell (y, x) was visited via a `t` move with `d-1` turns remaining
	//     if d == 0, its mean that the cell was not visited
	vst = new char**[RC];
	for (int t = 0; t < RC; t++) {
		vst[t] = new char*[h];			// 2d array
		for (int y = 0; y < h; y++)
			vst[t][y] = new char[w];	// 1d array
	}
}

Logic::~Logic() {
	for (int t = 0; t < RC; t++) {
		for (int y = 0; y < h; y++) 
			delete[] vst[t][y];
		delete[] vst[t];
	}
	delete[] vst;
}

/**
 * @ bfs
 * */
bool Logic::validate(int y0, int x0, int y1, int x1) {
	map = board->to_array();
	bool status = BFS(y0, x0, true, y1, x1);
	SaveLoader::del_map(map);
	return status;
}

bool Logic::suggest() {
	map = board->to_array();
	for (int y = 1; y < h-1; y++) for (int x = 1; x < w-1; x++) {
		if (map[y][x] != Gameboard::EmptyCell && BFS(y, x)) {
			SaveLoader::del_map(map);
			return true;
		}
	}
	SaveLoader::del_map(map);
	return false;
}


/**
 * @ bfs utils
 * */
void Logic::reset_vst() {
	// set all vst's content to 0
	for (int t = 0; t < RC; t++)
		for (int y = 0; y < h; y++)
			memset(vst[t][y], 0, sizeof(vst[t][y][0]) * w);
}

bool Logic::BFS(int y0, int x0, bool fixed, int y1, int x1) {
	// even the type is different
	if (fixed && map[y0][x0] != map[y1][x1]) return 0;

	// set up
	reset_vst();

	Deque<int> qy;	// y deque
	Deque<int> qx;	// x deque
	Deque<int> qt;	// the last turn taken
	Deque<int> qd;	// the number of turns remaining (depth+1)

	qy.push_back(y0);
	qx.push_back(x0);
	qt.push_back(RC);
	qd.push_back(MaxDepth+1);

	for (int t = 0; t < RC; t++)
		vst[t][y0][x0] = MaxDepth + 10;	// never to visit this cell again

	while (qy.count()) {
		int y = qy.pop_front(), 
		    x = qx.pop_front(), 
		    t = qt.pop_front(), 
		    d = qd.pop_front();
		for (int move = 0; move < RC; move++) {
			// check if index out of bound
			int nxtY = RY[move] + y,
			    nxtX = RX[move] + x;
			if (nxtY >= h || nxtX >= w || nxtY < 0 || nxtX < 0) continue;

			// check if out of turning points (maximum = 2)
			int nxtD = d;
			if (t != RC && move != t) nxtD--;
			if (nxtD == 0) continue;

			// this cell is already visited via a path with less depth
			if (vst[move][nxtY][nxtX] >= nxtD) continue;

			// check if found the destination
			if (fixed) {
				if (nxtY == y1 && nxtX == x1) return true;
			} else {
				if (map[nxtY][nxtX] == map[y0][x0]) return true;
			}

			// not an empty cell --> cant move here
			if (map[nxtY][nxtX] != Gameboard::EmptyCell) continue;

			// move to next cell
			qy.push_back(nxtY);
			qx.push_back(nxtX);
			qt.push_back(move);
			qd.push_back(nxtD);
		}
	}

	return false;
}
