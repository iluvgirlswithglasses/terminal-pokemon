
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Mar 20 08:08:34 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include <cstdio>
#include "scene-login.h"
#include "scene-config.h"
#include "lvl-menu-renderer.h"
#include "game-operator.h"

int main(int argc, const char* argv[]) {

#if _WIN32	// something to deal with windows' terrible performance
	WindowsConsole::init();
#endif

	// login
	Account acc = SceneLogin::start();

	// renderer
	Renderer* rdr = new Renderer();
	SceneConfig::start(rdr);

	// select level
	rdr->clrmap();
	rdr->render();
	LvlMenuRenderer menu(rdr, 6, 10, 32, 80);
	int dif, lvl, bgr = 0;
	rdr->wrtext(3, 43, "Select a level");
	menu.start(dif, lvl);

	// operate the game
	GameOperator game(rdr, dif, lvl, bgr);
	if (game.start()) 
		printf("you won --tmp\n");
	else
		printf("bruh --tmp\n");
	return 0;
}
