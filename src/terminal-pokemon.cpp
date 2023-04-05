
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
#include "scene-leaderboard.h"
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

void show_leaderboard(Renderer* rdr) {
	int dif, lvl;
	select_level(rdr, dif, lvl);
	rdr->clrmap();
	SceneLeaderboard::start(rdr, dif, lvl);
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
	rdr->clrmap();

	std::string res = "Your score: ";
	res += std::to_string(game.board->calc_score());
	rdr->wrtext(36, SceneLeaderboard::Left, res.c_str());
	for (uint8_t x = SceneLeaderboard::Left; x < SceneLeaderboard::Right; x++) {
		rdr->fgc[36][x] = Color::White;
		rdr->bgc[36][x] = Color::Purple;
		rdr->usg[36][x] = Renderer::UseBackground;
	}

	SceneLeaderboard::start(rdr, dif, lvl, acc);
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
