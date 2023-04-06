
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
	printf("welcome to the hacking console\n");
	printf("to read the content of a file, type `r <filedir>`\n");
	printf("to hack the content of a file, type `h <filedir>`\n");
	printf("for example: `r sav/00/iluvgirlswithglasses.bin`\n");
}

int HackingConsole::open_file(HackingSavefile& save, Account& acc) {
	return 0;
}

int HackingConsole::read_file(HackingSavefile& save, Account& acc) {
	return 0;
}

int HackingConsole::hack_file(HackingSavefile& save, Account& acc) {
	return 0;
}
