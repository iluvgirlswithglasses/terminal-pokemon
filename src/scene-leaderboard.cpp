
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Wed Apr  5 14:59:33 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "scene-leaderboard.h"

void SceneLeaderboard::start(Renderer* rdr, int dif, int lvl, Account& acc) {
	// headers
	rdr->wrtext(Top, Left, "Leaderboard for this level");
	rdr->wrtext(Top + 2, Left, "#");
	rdr->wrtext(Top + 2, Left + ColA, "Points");
	rdr->wrtext(Top + 2, Left + ColA + ColB, "Username");
	for (uint8_t x = Left; x < Right; x++) {
		rdr->fgc[Top][x] = Color::Cyan;
		rdr->thk[Top][x] = Color::Bold;
		rdr->usg[Top][x] = Renderer::UseThickness;

		rdr->fgc[Top + 2][x] = Color::White;
		rdr->bgc[Top + 2][x] = Color::Blue;
		rdr->usg[Top + 2][x] = Renderer::UseBackground;
	}

	// load saves
	std::string dir = "sav/";
	dir += (char) ('0' + dif); dir += (char) ('0' + lvl);
	dir += '/';
	Array<std::string> saves = FileFetcher::ls(dir);
	if (saves.len == 0) {
		render(rdr);
		return;
	}

	// fetch
	Deque<std::string> _usr;
	Deque<int> _pts;
	for (int i = 0; i < saves.len; i++)
		HackingAPI::read(saves[i], _usr, _pts);
	Array<std::string> usr = _usr.to_array();
	Array<int> pts = _pts.to_array();
	if (usr.len == 0) {
		render(rdr);
		return;
	}
	
	// sort
	Array<int> arr(usr.len);
	for (int i = 0; i < arr.len; i++)
		arr[i] = pts[i] << 8 | i;
	Qmath::quick_sort(arr.arr, 0, arr.len);
	for (int l = 0, r = arr.len - 1; l < r; l++, r--) {
		int tmp = arr[l];
		arr[l] = arr[r];
		arr[r] = tmp;
	}

	// data
	bool highlighted = false;
	std::string usrn = acc.usrn;

	for (int i = 0, y = Top + 4; i < std::min(arr.len, (int) DispLim); i++, y++) {
		std::string rank = std::to_string(i + 1);
		std::string score = std::to_string(arr[i]>>8);

		rdr->wrtext(y, Left, rank.c_str());
		rdr->wrtext(y, Left + ColA, score.c_str());
		rdr->wrtext(y, Left + ColA + ColB, usr[arr[i]&MSK8].c_str());

		for (uint8_t x = Left; x < Right; x++) {
			rdr->fgc[y][x] = Color::White;
			rdr->bgc[y][x] = Color::Black;
			rdr->usg[y][x] = Renderer::UseBackground;
		}

		if (!highlighted && usrn == usr[arr[i]&MSK8]) {
			highlighted = true;
			for (uint8_t x = Left; x < Right; x++) rdr->bgc[y][x] = Color::Purple;
		}
	}

	render(rdr);
}
