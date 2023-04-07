
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
	rdr = _rdr;

	// load data
	SaveLoader save;
	char** map = save.get_map();
	board = new Gameboard(map, SaveLoader::H, SaveLoader::W);
	SaveLoader::del_map(map);

	// load logic
	logic = new Logic(board);
}

Operator::~Operator() {
	delete board;
	delete logic;
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
