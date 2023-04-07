
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Fri Apr  7 11:13:37 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef LOGIC_H
#define LOGIC_H
// ------------------------------------------------------------

/*
the explaination of this class is writen in the main game
*/

#include <cstring>
#include "deque.h"
#include "gameboard.h"
#include "save-loader.h"

struct Logic {
	// move rules
	static const int RC = 4, RY[RC], RX[RC];
	static const int MaxDepth = 2;

	/** @ properties */
	int h, w;
	char**  map;
	char*** vst;
	Gameboard* board;

	/** @ constructors & deconstructors */
	Logic(Gameboard* board);
	~Logic();

	/** @ methods */
	bool validate(int y0, int x0, int y1, int x1);
	bool suggest();

	/** @ bfs */
	void reset_vst();
	bool BFS(int y0, int x0) { return BFS(y0, x0, false, 0, 0); }
	bool BFS(int y0, int x0, bool fixed, int y1, int x1);
};

#endif	// LOGIC_H
