
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Apr  3 15:08:49 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "hacking-api.h"

HackingSavefile HackingAPI::import(std::string& path) {
	// read
	HackingSavefile save;
	std::ifstream fi(path, std::ios::in | std::ios::binary);
	if (!fi.is_open()) {
		save.usrn[0] = '\0';	// mark this as open failed
		return save;
	}
	fi.read((char*) &save, sizeof(HackingSavefile));
	apply_mask(save);	// decode
	return save;
}

void HackingAPI::read(std::string& path, Deque<std::string>& usrn, Deque<int>& score) {
	HackingSavefile save = import(path);
	for (int i = 0; i < HackingParam::SaveLim && save.record[i].pts > 0; i++) {
		usrn.push_back(save.usrn);
		score.push_back(save.record[i].pts);
	}
}

void HackingAPI::write(std::string& path, Account& acc, GameOperator& opr) {
	// why this is constant is explain in the report
	// this is to deal with the design flaw of the statement giver
	static constexpr char Mask = 1<<7;

	int score = opr.board->calc_score();

	HackingSavefile save = import(path);	// decoded
	int assigned = 0;
	if (save.usrn[0] == '\0') {
		// i'm not reckless enough to do an initializer in hacking-template
		memset(save.usrn, 0, sizeof(save.usrn));
		memset(save.pass, 0, sizeof(save.pass));
		for (int i = 0; i < HackingParam::SaveLim; i++) {
			memset(save.state[i].board, 0, sizeof(save.state[i].board));
			memset(save.state[i].bgUrl, 0, sizeof(save.state[i].bgUrl));
			memset(save.state[i].__padding, 0, sizeof(save.state[i].__padding));
			memset(save.record[i].__padding, 0, sizeof(save.record[i].__padding));
		}
		// new savefile
		save.mask = Mask;
		strcpy(save.usrn, acc.usrn);
		strcpy(save.pass, acc.pass);
	} else {
		// continue to write on found savefile
		for (; assigned < HackingParam::SaveLim; assigned++) if (score > save.record[assigned].pts) {
			// shift by 1
			for (int i = HackingParam::SaveLim - 1; i > assigned; i--) {
				save.record[i] = save.record[i-1];
				save.state[i] = save.state[i-1];
			}
			break;
		}
	}

	// save record & state
	HackingRecord record;
	HackingState state;

	record.date = get_date();
	record.pts = score;

	state.h = (opr.board->h) - 2;
	state.w = (opr.board->w) - 2;
	state.y = 0;
	state.x = 0;
	for (int y = 0; y < state.h; y++) {
		for (int x = 0; x < state.w; x++) {
			int tile = opr.board->map[y+1][x+1];
			if (tile)
				state.board[y*state.w + x] = 'A' + tile - 1;
			else
				state.board[y*state.w + x] = 0;
		}
	}

	save.state[assigned] = state;
	save.record[assigned] = record;

	// background
	std::string bgr = opr.bgUrl;
	strcpy(state.bgUrl, bgr.c_str());

	// some padding
	memset(state.__padding, 0, sizeof(state.__padding));
	memset(record.__padding, 0, sizeof(record.__padding));

	// write to bin
	apply_mask(save);	// encode
	std::ofstream fo(path, std::ios::out | std::ios::binary);
	if (!fo.is_open()) return;	// your os is broken
	fo.write((char*) &save, sizeof(HackingSavefile));
	fo.close();
}

void HackingAPI::apply_mask(HackingSavefile& save) {
	mask(save.usrn, save.mask, HackingParam::UsrnLen);
	mask(save.pass, save.mask, HackingParam::PassLen);
	for (int i = 0; i < HackingParam::SaveLim; i++) {
		mask(save.state[i].board, save.mask, HackingParam::GameLen);
		mask(save.state[i].bgUrl, save.mask, HackingParam::PathLen);
	}
}

void HackingAPI::mask(char* str, char msk, int len) {
	for (int i = 0; i < len; i++) {
		if (!str[i]) return;
		str[i] ^= msk;
	}
}

HackingDate HackingAPI::get_date() {
	time_t now = time(0);
	tm *lct = localtime(&now);

	HackingDate date;
	date.yy = lct->tm_year;
	date.mm = lct->tm_mon;
	date.dd = lct->tm_mday;

	delete lct;
	return date;
}
