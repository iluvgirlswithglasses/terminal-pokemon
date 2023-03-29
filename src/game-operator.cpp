
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
	delete slidingLogic;
	delete rdr;
	delete gameRdr;
}

/**
 * @ main
 * 
 * returns `true` if win, `false` if otherwise
 * */
bool GameOperator::start(int diff) {
	difficulty = diff;

	// @ load game
	board = read();
	logic = get_logic(diff);
	rdr = new Renderer();
	gameRdr = new GameboardRenderer(board->map, rdr, board->h, board->w, 2, 1);

	if (difficulty >= DiffHardTop) slidingLogic = get_sliding_logic(diff);
	
	// @ cursor
	uint8_t cur_y = 1, cur_x = 1;
	uint32_t selection = 0;

	// @ init
	gameRdr->burn();
	gameRdr->draw_border(cur_y, cur_x, Color::Red);
	rdr->render();

	// @ iteration
#if __linux__	// --------------------------------------------------------------------------------
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
			if (board->map[cur_y][cur_x] == Gameboard::EmptyCell)
				continue;	// skip this iteration
			selection = (selection<<16) | (cur_y<<8) | cur_x;
			if (selection>>16) {
				if (handle_matching(selection) && difficulty >= DiffHardTop) {	
					// visualize_match() has not called gameRdr->burn()
					// so here it goes to render the removed cells first
					gameRdr->burn();
					gameRdr->draw_border(cur_y, cur_x, Color::Red);	// cursor
					rdr->render();

					uint8_t y0 = (selection>>24) & MSK8, 
					        x0 = (selection>>16) & MSK8, 
					        y1 = (selection>> 8) & MSK8, 
					        x1 = (selection    ) & MSK8;
					slide_tiles(y0, x0, y1, x1);
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
		// @ rendering
		// note that this block is executed after all operations above
		// and it'll override all changes those operations did to the screen
		gameRdr->burn();
		gameRdr->draw_border(cur_y, cur_x, Color::Red);	// cursor
		if (selection)
			gameRdr->draw_border(selection>>8&MSK8, selection&MSK8, Color::Green);	// selection a
		if (selection>>16)
			gameRdr->draw_border(selection>>24&MSK8, selection>>16&MSK8, Color::Green);	// selection b
		// linux terminal is strong enough
		// to just burn & re-render the whole screen after each frame 
		rdr->render();

		// @ gamestate check
		if (board->remaining == 0) return true;
		if (logic->suggest() == 0) return false;
	}
#elif _WIN32	// --------------------------------------------------------------------------------
	while (true) {
		char c = Input::wait_keypress();
		// windows' cursor must be unhovered manually
		gameRdr->burn();
		gameRdr->direct_render_cell(cur_y, cur_x);

		switch (c) {
		// @ handle moves
		case 'w': cur_y = cur_y == 0 ? cur_y : cur_y - 1; break;
		case 'a': cur_x = cur_x == 0 ? cur_x : cur_x - 1; break;
		case 's': cur_y = cur_y + 1 >= board->h ? cur_y : cur_y + 1; break;
		case 'd': cur_x = cur_x + 1 >= board->w ? cur_x : cur_x + 1; break;
		// @ handle selection
		case 'j':
			if (board->map[cur_y][cur_x] == Gameboard::EmptyCell) {
				// re-hover then skip this iteration
				gameRdr->draw_border(cur_y, cur_x, Color::Red);
				gameRdr->direct_render_cell(cur_y, cur_x);
				continue;
			}
			selection = (selection<<16) | (cur_y<<8) | cur_x;
			if (selection>>16) {
				if (handle_matching(selection) && difficulty >= DiffHardTop) {
					uint8_t y0 = (selection>>24) & MSK8, 
					        x0 = (selection>>16) & MSK8, 
					        y1 = (selection>> 8) & MSK8, 
					        x1 = (selection    ) & MSK8;
					// restore the cursor
					// since it was deleted along with the selected cells
					// in handle_matching() -> visualize_match()
					gameRdr->draw_border(cur_y, cur_x, Color::Red);
					gameRdr->direct_render_cell(cur_y, cur_x);
					slide_tiles(y0, x0, y1, x1);
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

		gameRdr->burn();
		gameRdr->draw_border(cur_y, cur_x, Color::Red);	// cursor
		if (selection)
			gameRdr->draw_border(selection>>8&MSK8, selection&MSK8, Color::Green);	// selection a
		if (selection>>16)
			gameRdr->draw_border(selection>>24&MSK8, selection>>16&MSK8, Color::Green);	// selection b
		// update modified cells
		// removed cells & slided cells are already handled in visualization methods
		gameRdr->direct_render_cell(cur_y, cur_x);
		gameRdr->direct_render_cell(selection>>8&MSK8, selection&MSK8);
		gameRdr->direct_render_cell(selection>>24&MSK8, selection>>16&MSK8);

		// @ gamestate check
		if (board->remaining == 0) return true;
		if (logic->suggest() == 0) return false;
	}
#endif			// __linux__ _WIN32 ---------------------------------------------------------------
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
	default:
		return new GameboardLogicNormal(board->h, board->w, board->map);
	}
}

SlidingLogic* GameOperator::get_sliding_logic(int diff) {
	switch (diff) {
	case GameOperator::DiffHardTop:
		return new SlidingLogic(board, 't');
	case GameOperator::DiffHardLft:
		return new SlidingLogic(board, 'l');
	case GameOperator::DiffHardDwn:
		return new SlidingLogic(board, 'd');
	case GameOperator::DiffHardRgt:
		return new SlidingLogic(board, 'r');
	}
	return new SlidingLogic(board, 'l');
}

/**
 * @ on-match handlers
 * */
bool GameOperator::handle_matching(uint32_t loc) {
	uint8_t y0 = (loc>>24) & MSK8, 
	        x0 = (loc>>16) & MSK8, 
	        y1 = (loc>> 8) & MSK8, 
	        x1 = (loc    ) & MSK8;
	if (logic->validate(y0, x0, y1, x1)) {
		board->map[y0][x0] = board->map[y1][x1] = Gameboard::EmptyCell;
		board->remaining -= 2;

		visualize_match(y0, x0, y1, x1);

		return true;
	}

#if _WIN32
	// selections must be deselected manually in windows
	gameRdr->draw_border(y0, x0, Color::White);
	gameRdr->draw_border(y1, x1, Color::White);
	gameRdr->direct_render_cell(y0, x0);
	gameRdr->direct_render_cell(y1, x1);
#endif

	return false;
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

	// leave the burning & rendering to main
}

void GameOperator::slide_tiles(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
	// this modifies the gameboard
	Deque<uint16_t> q0 = slidingLogic->slide(y0, x0);
	Deque<uint16_t> q1 = slidingLogic->slide(y1, x1);
	if (q0.count() == 0 && q1.count() == 0) return;

	sleep(400);
	if (q0.count() != 0) visualize_sliding(q0);
	if (q1.count() != 0) visualize_sliding(q1);
	rdr->render();
	sleep(400);

	// leave the burning & rendering to main
}

void GameOperator::visualize_sliding(Deque<uint16_t> &q) {
	if (q.count() == 0) return;
	uint16_t pre = q.pop_back();
	while (q.count()) {
		uint16_t nxt = q.pop_back();
		gameRdr->draw_path(pre>>8, pre&MSK8, nxt>>8, nxt&MSK8, Color::Red);
		pre = nxt;
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
}

void GameOperator::slide_tiles(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
	// this modifies the gameboard
	Deque<uint16_t> q0 = slidingLogic->slide(y0, x0);
	Deque<uint16_t> q1 = slidingLogic->slide(y1, x1);

	if (q0.count() == 0 && q1.count() == 0) return;

	sleep(400);
	visualize_sliding(q0, Color::Red);
	visualize_sliding(q1, Color::Red);
	sleep(400);

	// re-render all affected cells
	visualize_sliding(q0, Color::Black);
	visualize_sliding(q1, Color::Black);
	gameRdr->burn();
	while (q0.count()) {
		uint16_t loc = q0.pop_front();
		gameRdr->direct_render_cell(loc>>8, loc&MSK8);
	}
	while (q1.count()) {
		uint16_t loc = q1.pop_front();
		gameRdr->direct_render_cell(loc>>8, loc&MSK8);
	}
}

void GameOperator::visualize_sliding(Deque<uint16_t> &queue, char color) {
	if (queue.count() == 0) return;
	Deque<uint16_t> q = queue.clone();
	uint16_t pre = q.pop_front();
	while (q.count()) {
		uint16_t nxt = q.pop_front();
		gameRdr->draw_path(pre>>8, pre&MSK8, nxt>>8, nxt&MSK8, color);
		pre = nxt;
	}
}

#endif	// __linux__ _WIN32	-----------------------------------------------------------------------
