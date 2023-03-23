
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

// access to sleep
#include <chrono>
#include <thread>

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
	bool handle_matching(uint32_t loc);
	void visualize_match(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1);

	void sleep(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
};

#endif	// GAME_OPERATOR_H
