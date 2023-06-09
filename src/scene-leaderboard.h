
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Wed Apr  5 14:41:05 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef SCENE_LEADERBOARD_H
#define SCENE_LEADERBOARD_H
// ------------------------------------------------------------

#include <cstdint>

#include "array.h"
#include "deque.h"
#include "qmath.h"
#include "account.h"
#include "hacking-api.h"
#include "input.h"
#include "renderer.h"

/*
this object only render a part of the screen
you may use the other spaces however you want
*/

struct SceneLeaderboard {
	static constexpr uint8_t 
		Top = 5, Left = 17, Right = 84,
		ColA = 6, ColB = 10, ColC = 50, 
		DispLim = 25;
	
	static constexpr int MSK8 = (1<<8) - 1;

	static void start(Renderer* rdr, int dif, int lvl, Account& acc, int scored);

	static void start(Renderer* rdr, int dif, int lvl) {
		Account acc;
		start(rdr, dif, lvl, acc, -1);
	}

	static void render(Renderer* rdr) {
		rdr->render();
		Input::wait_keypress();
	}
};

#endif	// SCENE_LEADERBOARD_H
