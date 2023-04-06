
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

#include <string>

#include "color.h"
#include "deque.h"
#include "input.h"

#include "gameboard.h"
#include "gameboard-logic-easy.h"
#include "gameboard-logic-normal.h"
#include "sliding-logic.h"
#include "randomize-logic.h"

#include "file-io.h"
#include "renderer.h"
#include "gameboard-renderer.h"
#include "audio-player.h"

// access to sleep
#if __linux__
#include <chrono>
#include <thread>
#elif _WIN32
#include <windows.h>
#endif

/*
@ about this:
	operate the game scene
*/
class GameOperator {
public:
	// constructors & destructors
	GameOperator(Renderer* rdr, int diff, int lvl);
	~GameOperator();

	// start the game
	// once the game is finished:
	// return `1` --> the player won the game
	//        `0` otherwise
	bool start();

	// some stats after finishing the game
	Gameboard* board = nullptr;
	std::string bgUrl = "";

	// difficulty levels
	static constexpr int 
		DiffEasy = 0, 
		DiffNorm = 1, 
		DiffHardTop = 2,
		DiffHardLft = 3,
		DiffHardDwn = 4,
		DiffHardRgt = 5,
		DiffRand    = 6;
	int difficulty;

#if __linux__
	static void sleep(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
#elif _WIN32
	static void sleep(int ms) { Sleep(ms); }
#endif

protected:
	static constexpr uint32_t MSK8 = (1<<8) - 1;

	GameboardLogic* logic = nullptr;
	SlidingLogic* slidingLogic = nullptr;
	RandomizeLogic* randomLogic = nullptr;
	Renderer* rdr = nullptr;
	GameboardRenderer* gameRdr = nullptr;

	Gameboard* read(int diff, int lvl);

	GameboardLogic* get_logic(int diff);
	SlidingLogic* get_sliding_logic(int diff);

	// on-match
	bool handle_matching(uint32_t loc);
	void visualize_match(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1);

	// sliding tiles gamemode
	void slide_tiles(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1);
	void visualize_sliding(Deque<uint16_t> &q, char color);

	// rick ashley gamemode
	void randomize_tiles();
};

#endif	// GAME_OPERATOR_H
