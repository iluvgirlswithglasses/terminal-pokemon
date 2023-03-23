
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Thu Mar 23 19:00:44 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef GAME_OPERATOR_H
#define GAME_OPERATOR_H
// ------------------------------------------------------------

#include <cstdio>
#include "color.h"
#include "deque.h"
#include "input.h"

#include "gameboard.h"
#include "gameboard-logic-normal.h"
#include "renderer.h"
#include "gameboard-renderer.h"

/*
@ about this:
	operate the game scene
*/
class GameOperator {
public:
	// constructors & destructors
	GameOperator();
	~GameOperator();

	// start the game
	// only break once the game is finished
	void start();

	// maybe get some stats after finishing the game here

protected:
	static constexpr uint32_t MSK8 = (1<<8) - 1;

	// get the gameboard logic operator
	Gameboard* board;
	GameboardLogic* logic;
	Renderer* rdr;
	GameboardRenderer* gameRdr;

	// change this to reading files later
	Gameboard* read();

	// handle a match by player
	// return true if matched
	bool handle_matching(uint32_t loc) {
		uint8_t y0 = (loc>>24) & MSK8, 
		        x0 = (loc>>16) & MSK8, 
		        y1 = (loc>> 8) & MSK8, 
		        x1 = (loc    ) & MSK8;
		if (logic->validate(y0, x0, y1, x1)) {
			board->map[y0][x0] = board->map[y1][x1] = Gameboard::EmptyCell;
			// visualize here

			return true;
		}
		return false;
	}
};

#endif	// GAME_OPERATOR_H
