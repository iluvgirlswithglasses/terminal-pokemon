
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 15:30:45 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "lvl-menu-renderer.h"

LvlMenuRenderer::LvlMenuRenderer(Renderer* _rdr, uint8_t _t, uint8_t _l, uint8_t _h, uint8_t _w) {
	rdr = _rdr;
	top = _t;
	lft = _l;
	h = _h;
	w = _w;

	// rdr preset
	for (uint8_t y = top; y < top + h; y++) {
		for (uint8_t x = lft; x < lft + w; x++) {
			rdr->map[y][x] = ' ';
			rdr->usg[y][x] = Renderer::UseBackground;
			rdr->fgc[y][x] = Color::White;
			rdr->bgc[y][x] = Color::Black;
		}
	}

	// create `locY[]` `itemDif[]` `itemLvl[]`
	int crI = 0;
	uint8_t crY = top;
	for (int d = 0; d < LvlInfo::DiffCount; d++) {
		rdr->wrtext(crY++, lft, LvlInfo::DiffName[d].c_str());

		for (int i = 0; i < LvlInfo::DiffLvlCount[d]; i++) {
			rdr->wrtext(crY, lft + TabSize, "Level ");
			rdr->map[crY][lft + TabSize + 6] = (char) ('1' + i);

			locY[crI] = crY;
			itemDif[crI] = d;
			itemLvl[crI] = i;
			crI++;
			crY++;
		}
	}
}

#if __linux__	// ----------------------------------------------------------------------

void LvlMenuRenderer::start(int& dif, int& lvl) {
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
			cursor = cursor + 1 >= LvlInfo::LvlCount ? cursor : cursor + 1;
			break;
		case 'j':
			dif = itemDif[cursor];
			lvl = itemLvl[cursor];
			return;
		default:
			continue;	// repeat the while loop
		}
		select(cursor);
		rdr->render();
	}
}

void LvlMenuRenderer::select(int i) {
	uint8_t y = locY[i];
	for (uint8_t x = lft; x < lft + w; x++)
		rdr->bgc[y][x] = Color::Purple;
}

void LvlMenuRenderer::deselect(int i) {
	uint8_t y = locY[i];
	for (uint8_t x = lft; x < lft + w; x++)
		rdr->bgc[y][x] = Color::Black;
}

#elif _WIN32	// ----------------------------------------------------------------------

#include "windows-console.h"

void LvlMenuRenderer::start(int& dif, int& lvl) {
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
			cursor = cursor + 1 >= LvlInfo::LvlCount ? cursor : cursor + 1;
			break;
		case 'j':
			dif = itemDif[cursor];
			lvl = itemLvl[cursor];
			return;
		default:
			continue;	// repeat the while loop
		}
		select(cursor);
	}
}

void LvlMenuRenderer::select(int i) {
	uint8_t y = locY[i];
	for (uint8_t x = lft; x < lft + w; x++) {
		rdr->bgc[y][x] = Color::Purple;
		WindowsConsole::plot_pixel(rdr, y, x);
	}
	WindowsConsole::reset_cursor();
}

void LvlMenuRenderer::deselect(int i) {
	uint8_t y = locY[i];
	for (uint8_t x = lft; x < lft + w; x++) {
		rdr->bgc[y][x] = Color::Black;
		WindowsConsole::plot_pixel(rdr, y, x);
	}
	WindowsConsole::reset_cursor();
}

#endif			// ----------------------------------------------------------------------
