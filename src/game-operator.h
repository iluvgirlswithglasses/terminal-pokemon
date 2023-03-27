
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

#include <random>
#include <ctime>

#include "color.h"
#include "deque.h"
#include "input.h"

#include "gameboard.h"
#include "gameboard-logic-easy.h"
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
	void start(int diff);

	// maybe get some stats after finishing the game here

	// difficulty levels
	static constexpr int DiffEasy = 0, DiffNorm = 1, DiffHard = 2;
	int difficulty;

protected:
	static constexpr uint32_t MSK8 = (1<<8) - 1;

	// get the gameboard logic operator
	Gameboard* board;
	GameboardLogic* logic;
	Renderer* rdr;
	GameboardRenderer* gameRdr;

	// change this to reading files later
	Gameboard* read();

	GameboardLogic* get_logic(int diff);

	// handle a match by player
	// return true if matched
	bool handle_matching(uint32_t loc);
	void visualize_match(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1);

	// sliding tiles on hard difficulty
	void slide_tiles(uint32_t loc);
	void check_sliding_candidate(Deque<uint16_t> &candidates, uint8_t y0, uint8_t x0, int t);

	void sleep(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
};

#endif	// GAME_OPERATOR_H
