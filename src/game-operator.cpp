
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

#if _WIN32
		// windows' cursor must be unhovered manually
		// but you know what? gameRdr->burn() takes a few nanoseconds
		// while rendering only a 9x5 cell takes 25 miliseconds on windows
		gameRdr->burn();
		gameRdr->direct_render_cell(cur_y, cur_x);
		// i still dont know why windows is still popular
		// or office
#endif

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
					if (difficulty == DiffHard);	// add sliding logic here
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

#if __linux__	// ------------------------------------------------------------
		/* 
		linux terminal is strong enough
		to just burn & re-render the whole screen after each frame 
		*/
		rdr->render();
#elif _WIN32	// ------------------------------------------------------------
		/*
		windows terminal, on the other hand
		too bad
		*/
		// the removed cells are already render at `visualize_match`
		gameRdr->direct_render_cell(cur_y, cur_x);
		gameRdr->direct_render_cell(selection>>8&MSK8, selection&MSK8);
		gameRdr->direct_render_cell(selection>>24&MSK8, selection>>16&MSK8);
#endif			// __linux__ _WIN32 -------------------------------------------
	}
}

/**
 * @ loaders
 * */
Gameboard* GameOperator::read() {
	int h, w;
	scanf("%d%d", &h, &w);
	uint8_t** data = new uint8_t*[h];
	for (int i = 0; i < h; i++) {
		data[i] = new uint8_t[w];
		for (int j = 0; j < w; j++) 
			scanf("%2hhx", &data[i][j]);
			//     ^ this means unsigned char
			//       normally I'd just use "%d"
			//       but now I don't want to lie to my compiler
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

/**
 * @ on-match handlers
 * */
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

#if _WIN32
	// selections must be deselected manually in windows
	gameRdr->draw_border(y0, x0, Color::White);
	gameRdr->draw_border(y1, x1, Color::White);
	gameRdr->direct_render_cell(y0, x0);
	gameRdr->direct_render_cell(y1, x1);
#endif

	return MatchInvalid;
}

/**
 * @ matching visualizators
 * 
 * splited into 2 blocks: 
 * 		one for linux, another for windows
 * both block contains 2 methods:
 * 		visualize_match and slide_tiles
 * */
#if __linux__	// --------------------------------------------------------------------------------
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

#elif _WIN32	// --------------------------------------------------------------------------------
void GameOperator::visualize_match(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
	Deque<uint16_t> q = logic->get_path(y0, x0, y1, x1);
	Deque<uint16_t> p = q.clone();
	uint16_t pre = q.pop_front();
	while (q.count()) {
		uint16_t nxt = q.pop_front();
		gameRdr->draw_path(pre>>8, pre&MSK8, nxt>>8, nxt&MSK8, Color::Green);
		/*
		@FLAW

		by initial design, GameboardRenderer should never be allowed to 
		directly render anything to the screen,
		but to write GameboardContent to the Renderer only

		however, Windows' appalling performance broke every design ever
		so... deal with it

		the rendering for matching visuallization 
		will be done in gameRdr->draw_path()
		*/
		pre = nxt;
		sleep(150);
	}
	// redo the tracing visual
	pre = p.pop_front();
	while (p.count()) {
		uint16_t nxt = p.pop_front();
		gameRdr->draw_path(pre>>8, pre&MSK8, nxt>>8, nxt&MSK8, Color::Black);
		pre = nxt;
	}

	// erases the matched cells on screen
	gameRdr->burn();
	gameRdr->direct_render_cell(y0, x0);
	gameRdr->direct_render_cell(y1, x1);
	sleep(400);
}

#endif	// __linux__ _WIN32	-----------------------------------------------------------------------
