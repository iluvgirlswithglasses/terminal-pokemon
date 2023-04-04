
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
#include <ctime>
#include <random>
#include "scene-login.h"
#include "scene-config.h"
#include "scene-menu.h"
#include "lvl-menu-renderer.h"
#include "game-operator.h"

/**
 * @ options
 * */
void play_game(Renderer* rdr) {
	// select level
	rdr->clrmap();
	rdr->render();
	LvlMenuRenderer menu(rdr, 6, (100 - 60) / 2, 32, 60);
	int dif, lvl;
	rdr->wrtext(3, 20, "Select a level (\"W/S\" to move, \"J\" to select)");
	menu.start(dif, lvl);

	// operate the game
	GameOperator game(rdr, dif, lvl);
	if (game.start()) 
		printf("you won --tmp\n");
	else
		printf("bruh --tmp\n");
}

void show_leaderboard(Renderer* rdr) {

}

/**
 * @ drivers
 * */
int main(int argc, const char* argv[]) {
#if _WIN32	// something to deal with windows' terrible performance
	WindowsConsole::init();
#endif
	srand(time(0));	// srand will only be called here

	// login
	Account acc = SceneLogin::start();

	// renderer
	Renderer* rdr = new Renderer();
	SceneConfig::start(rdr);
	fflush(stdout);

	// game cycle
	while (true) {
		SceneMenu menu(rdr);
		int code = menu.start();
		switch (code) {
		case SceneMenu::PlayGame:
			play_game(rdr);
			break;
		case SceneMenu::Leaderboard:
			show_leaderboard(rdr);
			break;
		case SceneMenu::Exit:
			return 0;
		}
	}
	return 0;
}
