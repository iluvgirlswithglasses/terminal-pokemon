
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Thu Mar 23 19:03:14 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "game-operator.h"

/**
 * @ constructors & destructors
 * */
GameOperator::GameOperator() {

}

GameOperator::~GameOperator() {
	delete board;
	delete logic;
	delete rdr;
	delete gameRdr;
}

/**
 * @ main
 * */
void GameOperator::start() {
	// load game
	board = read();
	logic = new GameboardLogicNormal(board->h, board->w, board->map);
	rdr = new Renderer();
	gameRdr = new GameboardRenderer(board->map, rdr, board->h, board->w, 2, 1);
	
	// cursor
	uint8_t cur_y = 1, cur_x = 1;
	uint32_t selection = 0;

	// init
	gameRdr->burn();
	gameRdr->draw_border(cur_y, cur_x, Color::Red);
	rdr->render();
	// run
	while (true) {
		char c = Input::wait_keypress();
		switch (c) {
		// handle moves
		case 'w':
			cur_y = cur_y == 0 ? cur_y : cur_y - 1;
			break;
		case 's':
			cur_y = cur_y + 1 >= board->h ? cur_y : cur_y + 1;
			break;
		case 'a':
			cur_x = cur_x == 0 ? cur_x : cur_x - 1;
			break;
		case 'd':
			cur_x = cur_x + 1 >= board->w ? cur_x : cur_x + 1;
			break;
		// handle selection
		case 'j':
			selection = (selection<<16) | (cur_y<<8) | cur_x;
			if (selection>>16) {
				handle_matching(selection);
				selection = 0;
			}
			break;
		}
		// render
		gameRdr->burn();
		gameRdr->draw_border(cur_y, cur_x, Color::Red);	// cursor
		if (selection)
			gameRdr->draw_border(selection>>8&MSK8, selection&MSK8, Color::Green);	// selection a
		if (selection>>16)
			gameRdr->draw_border(selection>>24&MSK8, selection>>16&MSK8, Color::Green);	// selection b
		rdr->render();
	}
}

/**
 * @ deb
 * */
Gameboard* GameOperator::read() {
	int h, w;
	scanf("%d%d", &h, &w);
	uint8_t** data = new uint8_t*[h];
	for (int i = 0; i < h; i++) {
		data[i] = new uint8_t[w];
		for (int j = 0; j < w; j++) scanf("%d", &data[i][j]);
	}
	return new Gameboard(h, w, data);
}
