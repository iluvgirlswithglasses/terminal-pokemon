
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
	Array<std::string> usr(0);
	Array<int> pts(0);
	fetch(dif, lvl, usr, pts);

	if (usr.len == 0) return;

	Array<int> arr(usr.len);	// arr[i]: pts << 8 | usr_index
	for (int i = 0; i < arr.len; i++)
		arr[i] = pts[i] << 8 | i;
	if (arr.len > 1) {
		Qmath::quick_sort(arr.arr, 0, arr.len);
		for (int l = 0, r = arr.len - 1; l < r; l++, r--)
			std::swap(arr[l], arr[r]);	
	}

	rdr->wrtext(Top, 37, "Leaderboard for this level:");

	// table header
	rdr->wrtext(Top + 2, Left, "#");
	rdr->wrtext(Top + 2, Left + ColA, "Points");
	rdr->wrtext(Top + 2, Left + ColA + ColB, "Username");
	for (uint8_t x = Left; x < Right; x++) {
		rdr->fgc[Top + 2][x] = Color::Cyan;
		rdr->usg[Top + 2][x] = Renderer::UseThickness;
		rdr->thk[Top + 2][x] = Color::Bold;
	}

	// table content
	bool highlighted = false;
	std::string usrn = acc.usrn;

	for (int i = 0, y = Top + 4 + i; i < arr.len; i++, y++) {
		std::string rank = std::to_string(i + 1);
		std::string pont = std::to_string(arr[i] >> 8);
		std::string name = usr[ arr[i] & MSK8 ];

		rdr->wrtext(y, Left, rank.c_str());
		rdr->wrtext(y, Left + ColA, pont.c_str());
		rdr->wrtext(y, Left + ColA + ColB, name.c_str());

		for (uint8_t x = Left; x < Right; x++) {
			rdr->fgc[y][x] = Color::White;
			rdr->bgc[y][x] = Color::Black;
			rdr->usg[y][x] = Renderer::UseBackground;
		}

		if (!highlighted && usrn == name) {
			highlighted = true;
			for (uint8_t x = Left; x < Right; x++) rdr->bgc[y][x] = Color::Purple;
		}
	}

	rdr->render();
	Input::wait_keypress();
}

void SceneLeaderboard::fetch(int dif, int lvl, Array<std::string>& _usr, Array<int>& _pts) {
	// load saves
	std::string dir = "sav/";
	dir += (char) ('0' + dif); dir += (char) ('0' + lvl);
	dir += '/';
	Array<std::string> saves = FileFetcher::ls(dir);

	if (saves.len == 0) return;

	// fetch
	Deque<std::string> usr;
	Deque<int> pts;
	for (int i = 0; i < saves.len; i++)
		HackingAPI::read(saves[i], usr, pts);
	
	_usr = usr.to_array();
	_pts = pts.to_array();
}
