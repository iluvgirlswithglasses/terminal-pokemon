
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

	/**
	 * @ BFS
	 * */
	static constexpr int 
		MSK8 = (1<<8) - 1;
	static constexpr int
		RC = 4;
	static constexpr int 
		RY[RC] = {-1, 0, 1, 0, },	// relative `y` cells {t, l, d, r}
		RX[RC] = {0, -1, 0, 1, };	// relative `x` cells {t, l, d, r}

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
	}

	/**
	 * @ matcher
	 * */
	// check whether (y0, x0) can match with (y1, x1)
	bool validate(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
		if (map[y0][x0] != map[y1][x1]) return false;
		// bfs

		return false;
	}

	/**
	 * @ move suggestion
	 * */
	// automatically find a match pair
	// return format: `(y0<<24) | (x0<<16) | (y1<<8) | (x1<<0)`
	// if there's no match, `0` is returned (only happens when the board is corrupted)
	uint32_t suggest() {

		return 0;
	}

	// automatically find a match for (y0, x0)
	// return format: `y<<8|x`
	// if there's no match, `0` is returned
	uint16_t suggestBFS(uint8_t y0, uint8_t x0) {

		// visited
		bool** vst = new bool*[h];
		for (int y = 0; y < h; y++) {
			vst[y] = new bool[w];
			memset(vst[y], 0, sizeof(vst[y]) * w);
		}
		vst[y0][x0] = true;

		//
		Deque<uint16_t> q;	// bfs queue
		Deque<uint8_t>  d;	// (depth) number of turns performed (maximum = 2)
		Deque<uint8_t>  t;	// the last turning type

		q.push_back(key(y0, x0));
		d.push_back(0);
		t.push_back(RC);

		while (q.count()) {
			int y = q.front()>>8;
			int x = q.front()&MSK8;

			uint8_t depth = d.front();
			uint8_t turn  = t.front();
			q.pop_front();
			d.pop_front();
			t.pop_front();

			for (uint8_t move = 0; move < RC; move++) {
				int nxty32 = y + RY[move],
				    nxtx32 = x + RX[move];
				if (nxty32 >= h || nxtx32 >= w || nxty32 < 0 || nxtx32 < 0) continue;
				if (vst[nxty32][nxtx32]) continue;

				// check depth
				uint8_t nxtd = depth;
				if (turn != RC && move != turn) nxtd++;
				if (nxtd > 2) continue;

				// move to this new cell
				uint8_t nxty = nxty32, nxtx = nxtx32;
				if (map[nxty][nxtx] == map[y0][x0]) return key(nxty, nxtx);
				vst[nxty][nxtx] = true;

				q.push_back(key(nxty, nxtx));
				d.push_back(nxtd);
				t.push_back(move);
			}
		}

		return 0;
	}

private:
	/**
	 * @ decode 2 values into 1
	 * */
	uint16_t key(uint8_t y0, uint8_t x0) {
		uint16_t ans = y0;
		return ans<<8|x0;
	}

	uint32_t key(uint16_t a, uint16_t b) {
		uint32_t ans = a;
		return ans<<16|b;
	}
};
