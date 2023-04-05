
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
#include "lvl-info.h"
#include "lvl-menu-renderer.h"
#include "game-operator.h"
#include "hacking-api.h"

/**
 * @ options
 * */
void select_level(Renderer* rdr, int& dif, int& lvl) {
	// select level
	rdr->clrmap();
	rdr->render();
	LvlMenuRenderer menu(rdr, 6, (100 - 60) / 2, 32, 60);
	rdr->wrtext(3, 20, "Select a level (\"W/S\" to move, \"J\" to select)");
	menu.start(dif, lvl);
}

void show_leaderboard(Renderer* rdr, int dif, int lvl) {
	// load saves
	std::string dir = "sav/";
	dir += (char) ('0' + dif); dir += (char) ('0' + lvl);
	dir += '/';
	Array<std::string> saves = FileFetcher::ls(dir);

	// fetch
	Deque<std::string> players;
	Deque<int> scores;
	for (int i = 0; i < saves.len; i++) {
		HackingAPI::read(saves[i], players, scores);
	}

	rdr->clrmap();
	rdr->render();

	printf("leaderboard:\n");
	while (players.count()) {
		printf("%s %d\n", players.pop_front().c_str(), scores.pop_front());
	}
	Input::wait_keypress();
}

void show_leaderboard(Renderer* rdr) {
	int dif, lvl;
	select_level(rdr, dif, lvl);
	show_leaderboard(rdr, dif, lvl);
}

void play_game(Account& acc, Renderer* rdr) {
	int dif, lvl;
	select_level(rdr, dif, lvl);

	// operate the game
	GameOperator game(rdr, dif, lvl);
	int status = game.start();

	// savegame
	std::string savedir = LvlInfo::get_savefile(dif, lvl, acc);
	HackingAPI::write(savedir, acc, game);

	// show result
	if (status) {
		show_leaderboard(rdr, dif, lvl);
	} else {
		show_leaderboard(rdr, dif, lvl);
	}
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
			play_game(acc, rdr);
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
