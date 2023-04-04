
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 17:28:32 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "scene-menu.h"

std::string SceneMenu::Label[] = {
	"Play Game",
	"Leaderboard",
	"Exit"
};

SceneMenu::SceneMenu(Renderer* _rdr) {
	rdr = _rdr;
	rdr->clrmap();
	// backgrounds

	// buttons
	for (int i = 0; i < Options; i++) draw_cell(i);

	rdr->render();
}

void SceneMenu::draw_cell(int i) {
	// draw border
	uint8_t t = get_ry(i), d = get_ry(i+1);
	for (uint8_t x = Left; x <= Right; x++) 
		rdr->map[t][x] = rdr->map[d][x] = '-';
	for (uint8_t y = t; y <= d; y++)
		rdr->map[y][Left] = rdr->map[y][Right] = '|';
	rdr->map[t][Left] = rdr->map[t][Right] = rdr->map[d][Left] = rdr->map[d][Right] = '+';
	// draw text
	rdr->wrtext(ymid_allign(i), xmid_allign(i), Label[i].c_str());
}

void SceneMenu::select(int i) {
	set_bg(get_ry(i), Left, get_ry(i+1), Right, Color::Purple);
}

void SceneMenu::deselect(int i) {
	set_bg(get_ry(i), Left, get_ry(i+1), Right, Color::Black);
}

#if __linux__	// ----------------------------------------------------------------------

int SceneMenu::start() {
	int cursor = 0;
	select(cursor);
	rdr->render();

	while (true) {
		char c = Input::wait_keypress();
		switch (c) {
		case 'w':
			deselect(cursor);
			cursor = cursor - 1 < 0 ? cursor : cursor - 1;
			break;
		case 's':
			deselect(cursor);
			cursor = cursor + 1 >= Options ? cursor : cursor + 1;
			break;
		case 'j':
			return cursor;
		default:
			continue;	// repeat the while loop
		}
		select(cursor);
		rdr->render();
	}
}

void SceneMenu::set_bg(uint8_t t, uint8_t l, uint8_t d, uint8_t r, char color) {
	for (uint8_t y = t; y <= d; y++)
		for (uint8_t x = l; x <= r; x++)
			rdr->bgc[y][x] = color;
}

#elif _WIN32	// ----------------------------------------------------------------------

#include "windows-console.h"

int SceneMenu::start() {
	int cursor = 0;
	rdr->render();
	select(cursor);

	while (true) {
		char c = Input::wait_keypress();
		switch (c) {
		case 'w':
			deselect(cursor);
			cursor = cursor - 1 < 0 ? cursor : cursor - 1;
			break;
		case 's':
			deselect(cursor);
			cursor = cursor + 1 >= Options ? cursor : cursor + 1;
			break;
		case 'j':
			return cursor;
		default:
			continue;	// repeat the while loop
		}
		select(cursor);
	}
}

void SceneMenu::set_bg(uint8_t t, uint8_t l, uint8_t d, uint8_t r, char color) {
	for (uint8_t y = t; y <= d; y++) {
		for (uint8_t x = l; x <= r; x++) {
			rdr->bgc[y][x] = color;
			WindowsConsole::plot_pixel(rdr, y, x);
		}
	}
}

#endif			// ----------------------------------------------------------------------
