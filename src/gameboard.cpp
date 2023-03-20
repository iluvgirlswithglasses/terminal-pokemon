
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
	bool*** vst;

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

		// build visited
		resetVst();
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

	/**
	 * @ BFS
	 * */
	void resetVst();
};
