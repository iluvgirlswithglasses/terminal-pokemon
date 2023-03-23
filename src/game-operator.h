
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

    // debugging functions
    Gameboard* read();

protected:
    // get the gameboard logic operator
    Gameboard* board;
    GameboardLogic* logic;
    Renderer* rdr;
    GameboardRenderer* gameRdr;
};

#endif	// GAME_OPERATOR_H
