
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
 * 
 * returns `true` if win, `false` if otherwise
 * */
bool GameOperator::start(int diff) {
	std::srand(time(NULL));
	difficulty = diff;

	// load game
	board = read();
	logic = get_logic(diff);
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
				int matchCode = handle_matching(selection);

				switch (matchCode)
				{
				case MatchSuccess:
					if (difficulty == DiffHard) slide_tiles(selection);
					break;
				case MatchVictory:
					return true;
				case MatchGameover:
					return false;
				}
				selection = 0;
			}
			break;
		// suggestion
		case 'k':
			selection = logic->suggest();
			handle_matching(selection);
			selection = 0;
			break;
		// skip this iteration
		default:
			continue;
		}
		// rendering
		// note that this block is executed after all operations above
		// and it'll override all changes those operations did to the screen
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
 * @ utils
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

GameboardLogic* GameOperator::get_logic(int diff) {
	switch (diff) {
	case GameOperator::DiffEasy:
		return new GameboardLogicEasy(board->h, board->w, board->map);
	case GameOperator::DiffNorm:
	case GameOperator::DiffHard:
	default:
		return new GameboardLogicNormal(board->h, board->w, board->map);
	}
}

int GameOperator::handle_matching(uint32_t loc) {
	uint8_t y0 = (loc>>24) & MSK8, 
	        x0 = (loc>>16) & MSK8, 
	        y1 = (loc>> 8) & MSK8, 
	        x1 = (loc    ) & MSK8;
	if (logic->validate(y0, x0, y1, x1)) {
		board->map[y0][x0] = board->map[y1][x1] = Gameboard::EmptyCell;
		board->remaining -= 2;

		visualize_match(y0, x0, y1, x1);

		if (board->remaining == 0) return MatchVictory;
		if (logic->suggest() == 0) return MatchGameover;

		return MatchSuccess;
	}
	return MatchInvalid;
}

void GameOperator::visualize_match(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
	Deque<uint16_t> q = logic->get_path(y0, x0, y1, x1);
	uint16_t pre = q.pop_front();
	while (q.count()) {
		uint16_t nxt = q.pop_front();
		gameRdr->draw_path(pre>>8, pre&MSK8, nxt>>8, nxt&MSK8, Color::Green);
		rdr->render();
		pre = nxt;
		sleep(150);
	}
}

void GameOperator::slide_tiles(uint32_t loc) {
	uint8_t y1 = (loc>> 8) & MSK8, 
	        x1 = (loc    ) & MSK8;
	Deque<uint16_t> candidates;
	for (int t = 0; t < GameboardLogic::RC; t++) {
		check_sliding_candidate(candidates, y1, x1, t);
	}
	if (candidates.count() == 0) return;

	uint16_t chosen = candidates.get_index(std::rand() % candidates.count());
	uint8_t cy = chosen>>8, cx = chosen&MSK8;

	// erases the matched cells on screen first
	gameRdr->burn();
	rdr->render();
	sleep(400);

	// then draw a line which indicates the incoming sliding tile
	gameRdr->draw_path(cy, cx, y1, x1, Color::Red);
	rdr->render();
	sleep(400);

	// update the gameboard (the rest of the rendering is up to the main function)
	board->map[y1][x1] = board->map[cy][cx];
	board->map[cy][cx] = Gameboard::EmptyCell;
}

void GameOperator::check_sliding_candidate(Deque<uint16_t> &candidates, uint8_t y0, uint8_t x0, int t) {
	int ny = logic->RY[t] + y0, nx = logic->RX[t] + x0;
	if (ny < 0 || nx < 0 || ny >= board->h || nx >= board->w) return;
	if (board->map[ny][nx] != Gameboard::EmptyCell) 
		candidates.push_back(ny<<8|nx);
}
