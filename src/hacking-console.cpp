
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Thu Apr  6 13:21:28 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "hacking-console.h"

void HackingConsole::start(Account& acc) {
	// greeting
	fflush(stdout);
	printf("\n\n");
	printf("welcome to the hacking console\n");
	printf("to read the content of a file, type `r <filedir>`\n");
	printf("to hack the content of a file, type `h <filedir>`\n");
	printf("to exit this console, type `c`\n");
	printf("for example: `r sav/00/iluvgirlswithglasses.bin`\n\n");

	while (true) {
		printf(">>> ");

		char c;
		std::string s;
		std::cin >> c;

		// perform action
		switch (c) {
		case 'r':
			std::cin >> s;
			read_file(acc, s);
			break;
		case 'h':
			std::cin >> s;
			hack_file(acc, s);
			break;
		case 'c':
			return;
		default:
			break;
		}
	}
}

int HackingConsole::read_file(Account& acc, std::string& url) {

	HackingSavefile save = HackingAPI::import(url);
	if (save.usrn[0] == '\0') {
		printf("save file does not exists\n");
		return OpenFailed;
	}
	if (strcmp(acc.usrn, save.usrn) != 0) {
		printf("you are not the owner of this save file\n");
		return PermissionDenied;
	}

	int records = 0;
	for (; records < HackingParam::SaveLim && save.record[records].pts > 0; records++);

	// print all information
	printf("------ savefile information ------\n\n");
	printf("username: %s\n", save.usrn);
	printf("records count: %d\n", records);

	for (int i = 0; i < records; i++) {
		printf("\nrecord number #%d\n", i+1);

		HackingRecord record = save.record[i];
		HackingState state = save.state[i];

		printf("    date: %d-%d-%d\n", record.date.dd, record.date.mm, record.date.yy);
		printf("    score: %d\n", record.pts);
		printf("    background url: %s\n", state.bgUrl);
		printf("    board size: %dx%d\n", state.h, state.w);
		printf("    cursor: (%d, %d)\n", state.y, state.x);
		printf("    board:\n");
		for (int y = 0; y < state.h; y++) {
			printf("    ");
			for (int x = 0; x < state.w; x++) {
				char tile = state.board[y*state.w + x];
				if (tile > 0)
					printf("%c ", tile);
				else
					printf(". ");
			}
			printf("\n");
		}
	}

	return OpenSucceed;
}

int HackingConsole::hack_file(Account& acc, std::string& url) {
	HackingSavefile save = HackingAPI::import(url);
	if (save.usrn[0] == '\0') {
		printf("save file does not exists\n");
		return OpenFailed;
	}
	if (strcmp(acc.usrn, save.usrn) != 0) {
		printf("you are not the owner of this save file\n");
		return PermissionDenied;
	}

	int records = 0;
	for (; records < HackingParam::SaveLim && save.record[records].pts > 0; records++);

	printf("found %d records, choose one in range [0;%d) to modify:\n", records, records);
	
	int chosen = 0;
	std::cin >> chosen;
	if (chosen < 0 || records <= chosen) {
		printf("invalid range, existing...\n");
		return OpenFailed;
	}

	// now just modify whatever i can think of
	HackingRecord& record = save.record[chosen];
	HackingState& state = save.state[chosen];

	printf("give a new score (currently %d): ", record.pts);
	std::cin >> record.pts;

	printf("modify date (currently %d-%d-%d) (type in `day month year` format): ", record.date.dd, record.date.mm, record.date.yy);
	std::cin >> record.date.dd >> record.date.mm >> record.date.yy;

	printf("modify background directory (currently %s): ", state.bgUrl);
	std::cin >> state.bgUrl;

	printf("modify the board\n");
	printf("type in %d rows, %d columns,\n", state.h, state.w);
	printf("use capitalized english character to indicate remaining tiles,\n");
	printf("and a dot \".\" to indicate an empty cell.\n");

	for (int y = 0; y < state.h; y++) {
		for (int x = 0; x < state.w; x++) {
			char c; std::cin >> c;
			if (c == '.') state.board[y*state.w + x] = 0;
			else state.board[y*state.w + x] = c;
		}
	}

	HackingAPI::write(save, url);
	printf("action completed\n");

	return OpenSucceed;
}
