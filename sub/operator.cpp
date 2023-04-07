
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Fri Apr  7 16:55:42 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "operator.h"

Operator::Operator(Renderer* _rdr, char ori) {
	orientation = ori;

	// load data
	SaveLoader save;
	char** map = save.get_map();
	board = new Gameboard(map, SaveLoader::H, SaveLoader::W);
	SaveLoader::del_map(map);

	// load logic
	logic = new Logic(board);

	// load renderer
	rdr = _rdr;
	gameRdr = new GameboardRenderer(board, rdr);
}

Operator::~Operator() {
	delete board;
	delete logic;
	delete gameRdr;
}

void Operator::slide(int y, int x) {
	switch (orientation) {
	case 't': board->slide_top(y, x); break;
	case 'l': board->slide_lft(y, x); break;
	case 'd': board->slide_dwn(y, x); break;
	case 'r': board->slide_rgt(y, x); break;

	default:  board->slide_dwn(y, x); break;
	}
}

bool Operator::handle_matching(int loc) {
	int y0 = (loc>>24) & MSK8, 
	    x0 = (loc>>16) & MSK8, 
	    y1 = (loc>> 8) & MSK8, 
	    x1 = (loc    ) & MSK8;
	if (logic->validate(y0, x0, y1, x1)) {
		slide(y0, x0);
		slide(y1, x1);
		board->remaining -= 2;
		return true;
	}
	return false;
}

/**
 * @ game thread
 * */
bool Operator::start() {
	// @ cursor
	int cur_y = 1, cur_x = 1;
	int selection = 0;

	// @ init
	gameRdr->burn();
	gameRdr->draw_border(cur_y, cur_x, Renderer::Red);
	rdr->render();

	// @ iteration
	while (true) {
		char c = Input::wait_keypress();
		switch (c) {
		// @ handle moves
		case 'w': cur_y = cur_y == 0 ? cur_y : cur_y - 1; break;
		case 'a': cur_x = cur_x == 0 ? cur_x : cur_x - 1; break;
		case 's': cur_y = cur_y + 1 >= board->h ? cur_y : cur_y + 1; break;
		case 'd': cur_x = cur_x + 1 >= board->w ? cur_x : cur_x + 1; break;
		// @ handle selection
		case 'j':
			if (board->get_value(cur_y, cur_x) == Gameboard::EmptyCell)
				continue;	// skip this iteration
			selection = (selection<<16) | (cur_y<<8) | cur_x;
			if (selection>>16) {
				handle_matching(selection);
				selection = 0;
			}
			break;
		// skip this iteration
		default:
			continue;
		}
		gameRdr->burn();
		gameRdr->draw_border(cur_y, cur_x, Renderer::Red);	// cursor
		if (selection)
			gameRdr->draw_border(selection>>8&MSK8, selection&MSK8, Renderer::Green);
		rdr->render();

		// @ gamestate check
		if (board->remaining == 0) return true;
		if (logic->suggest() == 0) return false;
	}
}
