
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Apr  3 14:47:04 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef HACKING_TEMPLATE_H
#define HACKING_TEMPLATE_H
// ------------------------------------------------------------

#include "hacking-param.h"

/*
@ about this:
	the hacking template
	as required in project statement
*/

struct HackingState {
	int h, w;	// boardgame size
	int y, x;	// cursor
	char board[HackingParam::GameLen];
	char bgUrl[HackingParam::PathLen];
	// 500 byte NULL
};

struct HackingDate {
	int dd, mm, yy;
};

struct HackingRecord {
	HackingDate date;
	int pts;
	// 500 byte NULL
};

struct HackingSavefile {
	char mask;
	char usrn[HackingParam::UsrnLen];
	char pass[HackingParam::PassLen];
	HackingRecord record[HackingParam::SaveLim];
	HackingState state[HackingParam::SaveLim];
	// The statement requires 500 byte NULL here
	// but the sample bin file does not
	// so I'm not gonna put it here
};

#endif	// HACKING_TEMPLATE_H
