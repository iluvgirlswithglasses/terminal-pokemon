
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
GameOperator::GameOperator(Renderer* _rdr, int diff, int lvl) {
	difficulty = diff;

	board = read(diff, lvl);
	logic = get_logic(diff);
	rdr = _rdr;
	gameRdr = new GameboardRenderer(board->map, rdr, board->h, board->w, 2, 1);

	if (DiffHardTop <= difficulty && difficulty <= DiffHardRgt) 
		slidingLogic = get_sliding_logic(diff);
	if (difficulty == DiffRand)
		randomLogic = new RandomizeLogic(board);
}

GameOperator::~GameOperator() {
	delete board;
	delete logic;
	delete rdr;
	delete gameRdr;

	if (slidingLogic != nullptr) delete slidingLogic;
	if (randomLogic != nullptr) delete randomLogic;
}

/**
 * @ main
 * 
 * returns `true` if win, `false` if otherwise
 * */
bool GameOperator::start() {
	
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
				bool status = handle_matching(selection);

				// sliding tiles
				if (status && DiffHardTop <= difficulty && difficulty <= DiffHardRgt) {	
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

				// randomize
				if (status && difficulty == DiffRand && rand() % 4 == 0) {
					gameRdr->burn();
					gameRdr->draw_border(cur_y, cur_x, Color::Red);	// cursor
					rdr->render();

					randomize_tiles();
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
		bool status = false, jpressed = false;
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
			jpressed = true;
			if (board->map[cur_y][cur_x] == Gameboard::EmptyCell) {
				// re-hover then skip this iteration
				gameRdr->draw_border(cur_y, cur_x, Color::Red);
				gameRdr->direct_render_cell(cur_y, cur_x);
				continue;
			}
			selection = (selection<<16) | (cur_y<<8) | cur_x;
			if (selection>>16) {
				status = handle_matching(selection);
				// sliding tiles
				if (status && DiffHardTop <= difficulty && difficulty <= DiffHardRgt) {
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
				// randomizers
				if (status && difficulty == DiffRand && rand() % 4 == 0) {
					// restore the cursor
					gameRdr->draw_border(cur_y, cur_x, Color::Red);
					gameRdr->direct_render_cell(cur_y, cur_x);
					randomize_tiles();
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

		// audio plays after all rendering are done
		if (jpressed) {
			if (status) 				// there's a match in this iteration
				AudioPlayer::play(AudioPlayer::B, 400);
			else if (selection == 0) 	// invalid match
				AudioPlayer::play(AudioPlayer::C, 400);
		}
	}
#endif			// __linux__ _WIN32 ---------------------------------------------------------------
}

/**
 * @ loaders
 * */
Gameboard* GameOperator::read(int diff, int lvl) {
	//                        0123456789
	static char FileName[] = "lvl/xx.bin";

	int lvlPack = diff;
	if (DiffNorm <= diff && diff <= DiffHardRgt) lvlPack = DiffNorm;
	FileName[4] = '0' + lvlPack;
	FileName[5] = '0' + lvl;

	uint8_t h, w, **data;
	FileIO::read_lvl(FileName, data, h, w);
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
	if (q0.count() != 0) visualize_sliding(q0, Color::Red);
	if (q1.count() != 0) visualize_sliding(q1, Color::Red);
	rdr->render();
	sleep(400);

	// leave the burning & rendering to main
}

void GameOperator::visualize_sliding(Deque<uint16_t> &q, char color) {
	if (q.count() == 0) return;
	uint16_t pre = q.pop_back();
	while (q.count()) {
		uint16_t nxt = q.pop_back();
		gameRdr->draw_path(pre>>8, pre&MSK8, nxt>>8, nxt&MSK8, color);
		pre = nxt;
	}
}

void GameOperator::randomize_tiles() {
	// this modifies the gameboard
	Array<uint32_t> a = randomLogic->randomize();
	if (a.len == 0) return;

	for (int i = 0; i < a.len; i++) {
		uint32_t loc = a[i];
		uint8_t y0 = (loc>>24) & MSK8, 
		        x0 = (loc>>16) & MSK8, 
		        y1 = (loc>> 8) & MSK8, 
		        x1 = (loc    ) & MSK8;
		gameRdr->draw_path(y0, x0, y1, x1, Color::Red);
	}
	rdr->render();	// the modified board is not yet burned
	sleep(400);
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

	// no need to sleep here because AudioPlayer did that already
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

void GameOperator::randomize_tiles() {
	// this modifies the gameboard
	Array<uint32_t> a = randomLogic->randomize();
	if (a.len == 0) return;

	for (int i = 0; i < a.len; i++)
		gameRdr->draw_path(a[i]>>24&MSK8, a[i]>>16&MSK8, a[i]>>8&MSK8, a[i]&MSK8, Color::Red);
	sleep(400);
	for (int i = 0; i < a.len; i++)
		gameRdr->draw_path(a[i]>>24&MSK8, a[i]>>16&MSK8, a[i]>>8&MSK8, a[i]&MSK8, Color::Black);

	gameRdr->burn();
	for (int i = 0; i < a.len; i++) {
		gameRdr->direct_render_cell(a[i]>>24&MSK8, a[i]>>16&MSK8);
		gameRdr->direct_render_cell(a[i]>> 8&MSK8, a[i]    &MSK8);
	}
}

#endif	// __linux__ _WIN32	-----------------------------------------------------------------------
