
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
#include "sliding-logic.h"

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
	// once the game is finished:
	// return `1` --> the player won the game
	//        `0` otherwise
	bool start(int diff);

	// maybe get some stats after finishing the game here

	// difficulty levels
	static constexpr int 
		DiffEasy = 0, 
		DiffNorm = 1, 
		DiffHardTop = 2,
		DiffHardLft = 3,
		DiffHardDwn = 4,
		DiffHardRgt = 5;
	int difficulty;

protected:
	static constexpr uint32_t MSK8 = (1<<8) - 1;

	// get the gameboard logic operator
	Gameboard* board;
	GameboardLogic* logic;
	SlidingLogic* slidingLogic;
	Renderer* rdr;
	GameboardRenderer* gameRdr;

	// change this to reading files later
	Gameboard* read();

	GameboardLogic* get_logic(int diff);
	SlidingLogic* get_sliding_logic(int diff);

	bool handle_matching(uint32_t loc);
	void visualize_match(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1);

	void slide_tiles(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1);
#if __linux__
	void visualize_sliding(Deque<uint16_t> &q);
#elif _WIN32
	void visualize_sliding(Deque<uint16_t> &q, char color);
#endif

	void sleep(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
};

#endif	// GAME_OPERATOR_H
