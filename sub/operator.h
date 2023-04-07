
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Fri Apr  7 16:46:02 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef OPERATOR_H
#define OPERATOR_H
// ------------------------------------------------------------

#include "gameboard.h"
#include "logic.h"
#include "input.h"
#include "renderer.h"
#include "gameboard-renderer.h"

struct Operator {
	/** @ properties */
	Gameboard* board;
	Logic* logic;
	char orientation;

	GameboardRenderer* gameRdr;
	Renderer* rdr;

	/** @ stuffs */
	Operator(Renderer* rdr, char orientation);
	~Operator();

	bool start();	// true if player wins
	void slide(int y, int x);
};

#endif	// OPERATOR_H
