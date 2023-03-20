
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Mar 20 11:15:01 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include <cstdint>
#include <cstring>
#include "deque.cpp"

/*
@ about this:
	operates the gameboard
*/

struct GameBoard {
public:
	/**
	 * @ special values
	 * */
	static constexpr uint8_t EmptyCell = 0;
	static constexpr int MSK8 = (1<<8) - 1;	// 1111 1111

	/**
	 * @ public fields
	 * */
	uint8_t h, w;
	uint8_t** map;

	/**
	 * @ constructors
	 * */
	GameBoard(uint8_t _h, uint8_t _w, uint8_t** gamedata) {
		// assume the area of the board which contains tiles has the size of _h*_w
		// then the size of `map` is (_h+2)*(_w+2), or h*w
		// which implies `map` has a 1 unit padding for each edge
		h = _h + 2, w = _w + 2;
		map = new uint8_t*[h];

		// top && down
		map[0] = new uint8_t[w];
		memset(map[0], EmptyCell, sizeof(map[0][0]) * w);
		map[h-1] = new uint8_t[w];
		memset(map[h-1], EmptyCell, sizeof(map[h-1][0]) * w);

		// paste the gamedata into the map
		for (int y = 0; y < _h; y++) {
			map[y+1] = new uint8_t[w];										// allocate this row
			map[y+1][0] = map[y+1][w-1] = EmptyCell; 						// left & right
			memcpy(map[y+1] + 1, gamedata[y], sizeof(gamedata[y][0]) * _w); // mid
		}

		prepBFS();
	}

	~GameBoard() {
		deprebBFS();
		for (int y = 0; y < h; y++) delete[] map[y];
		delete[] map;
	}

	/**
	 * @ validator
	 * 
	 * check if (y0, x0) can be matched with (y1, x1)
	 * */
	bool validate(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
		return BFS(y0, x0, true, y1, x1);
	}

	/**
	 * @ suggestion
	 * 
	 * brute force to find a matching pair (y0, x0) (y1, x1)
	 * returns in following format:
	 * 		(y0<<24) | (x0<<16) | (y1<<8) | (x1<<0)
	 * */
	uint32_t suggest() {
		for (int y = 1; y < h-1; y++) for (int x = 1; x < w-1; x++) if (map[y][x] != EmptyCell) {
			uint32_t self  = (y<<8|x)<<16;
			uint16_t other = BFS(y, x);
			if (other != 0) return self|other;
		}
		return 0; // the map is corrupted
	}

	/**
	 * @ tracer
	 * 
	 * get the path from (y0, x0) -> (y1, x1)
	 * which was previously traced
	 * */
	Deque<uint16_t> get_path(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
		Deque<uint16_t> ans;
		uint8_t depth = 3;
		for (int d = 0; d < 3; d++) if (vst[d][y1][x1]) {
			depth = d;
			break;
		}
		ans.push_front(y1<<8|x1);
		traceDFS(ans, y0, x0, y1, x1, depth);
		return ans;
	}

private:
	/**
	 * @ BFS helpers
	 * */
	bool*** vst;
	uint32_t*** trace;

	void prepBFS() {
		// vst[d][y, x] == true
		// --> cell (y, x) was visited via `d` turns
		vst = new bool**[3];
		for (int d = 0; d < 3; d++) {
			vst[d] = new bool*[h];			// 2d array
			for (int y = 0; y < h; y++)
				vst[d][y] = new bool[w];	// 1d array
		}
		// trace[d][y, x] == (pd<<16) | (py<<8) | px
		//                   where `p` means parent
		trace = new uint32_t**[3];
		for (int d = 0; d < 3; d++) {
			trace[d] = new uint32_t*[h];
			for (int y = 0; y < h; y++)
				trace[d][y] = new uint32_t[w];
		}
	}

	void deprebBFS() {
		// clear BFS memory usage
		// or what I call "de-preparation"
		for (int d = 0; d < 3; d++) {
			for (int y = 0; y < h; y++) {
				delete[] vst[d][y];
				delete[] trace[d][y];
			}
			delete[] vst[d];
			delete[] trace[d];
		}
		delete[] vst;
		delete[] trace;
	}

	void resetVst() {
		// set all vst's content to 0
		for (int d = 0; d < 3; d++)
			for (int y = 0; y < h; y++)
				memset(vst[d][y], 0, sizeof(vst[d][y][0]) * w);
	}

	// encodes (y, x)
	uint16_t key(uint8_t y0, uint8_t x0) {
		uint16_t ans = y0;
		return ans<<8|x0;
	}

	/**
	 * @ BFS
	 * 
	 * if fixed == false:
	 * 		finds (y1, x1) which (y0, x0) can be matched with
	 * 		if there is no such cell, returns 0
	 * if fixed == true:
	 * 		check if (y0, x0) can be matched with (y1, x1)
	 * 
	 * return format:
	 * 		y<<8|x
	 * */
	uint16_t BFS(uint8_t y0, uint8_t x0, bool fixed = false, uint8_t y1 = 0, uint8_t x1 = 0) {
		// BFS settings
		static constexpr int
			RC = 4;
		static constexpr int 
			RY[RC] = { -1, 0, 1, 0, },	// relative `y` cells {t, l, d, r}
			RX[RC] = { 0, -1, 0, 1, };	// relative `x` cells {t, l, d, r}

		// even the type is different
		if (fixed && map[y0][x0] != map[y1][x1]) return 0;

		// set up
		resetVst();

		Deque<uint8_t> qy;	// y deque
		Deque<uint8_t> qx;	// x deque
		Deque<uint8_t> qt;	// the last turn taken
		Deque<uint8_t> qd;	// the number of turns taken (depth)

		qy.push_back(y0);
		qx.push_back(x0);
		qt.push_back(RC);
		qd.push_back(0);

		vst[0][y0][x0] = vst[1][y0][x0] = vst[2][y0][x0] = true;

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
				if (t != RC && move != t) nxtD++;
				if (nxtD > 2) continue;

				// this cell is already visited
				if (vst[nxtD][nxtY][nxtX]) continue;

				// check if found the destination
				if (fixed) {
					if (nxtY == y1 && nxtX == x1) ans = key(nxtY, nxtX);
				} else {
					if (map[nxtY][nxtX] == map[y0][x0]) ans = key(nxtY, nxtX);
				}

				// trace
				vst[nxtD][nxtY][nxtX] = true;
				trace[nxtD][nxtY][nxtX] = (static_cast<uint32_t>(d)<<16) | (static_cast<uint32_t>(y)<<8) | (static_cast<uint32_t>(x));

				if (ans != 0) return ans;	// only returns after tracing

				// not an empty cell --> cant move here
				if (map[nxtY][nxtX] != EmptyCell) continue;

				// move to next cell
				qy.push_back(nxtY);
				qx.push_back(nxtX);
				qt.push_back(move);
				qd.push_back(nxtD);
			}
		}

		return 0;
	}

	/**
	 * @ tracer
	 * */
	void traceDFS(Deque<uint16_t> &q, uint8_t dy, uint8_t dx, uint8_t y, uint8_t x, uint8_t d) {
		uint32_t nxt = trace[d][y][x];
		uint8_t nxtX = nxt       & MSK8,
		        nxtY = (nxt>>8)  & MSK8,
		        nxtD = (nxt>>16) & MSK8;
		q.push_front(nxtY<<8|nxtX);
		if (nxtY == dy && nxtX == dx) return;
		traceDFS(q, dy, dx, nxtY, nxtX, nxtD);
	}
};
