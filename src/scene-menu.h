
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 17:24:55 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef SCENE_MENU_H
#define SCENE_MENU_H
// ------------------------------------------------------------

#include <cstdint>
#include <string>
#include "param.h"
#include "input.h"
#include "renderer.h"

struct SceneMenu {
public:
	static constexpr int Options = 3;
	static constexpr std::string Label[Options];

	static constexpr int 
		PlayGame = 0,
		Leaderboard = 1,
		Exit = 2;

	SceneMenu(Renderer* rdr);
	int start();

private:
	static constexpr uint8_t 
		CellWidth = 25, 
		CellHeight = 5,
		Top = (Param::ScreenHeight - 2 - CellHeight * (Options + 1)),
		Down = Top + CellHeight * (Options + 1), 
		Left = (Param::ScreenWidth - CellWidth) >> 1,
		Right = Left + CellWidth - 1;

	Renderer* rdr;

	void draw_cell(int i);

	void select(int i);
	void deselect(int i);
	void set_bg(uint8_t t, uint8_t l, uint8_t d, uint8_t r, char color);

	uint8_t get_ry(int i) { return Top + CellHeight * i; }
	uint8_t xmid_allign(int len) { return Left + ((CellWidth - len) >> 1); }
	uint8_t ymid_allign(int i) { return get_ry(i) + CellHeight >> 1; }
};

#endif	// SCENE_MENU_H
