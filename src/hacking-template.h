
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

@ note:
	some of these structures has excessive memory allocation
	(property `__padding[HackingParam::Padding]`)

	this DOES NOT cause any memory leak, nor waste any memory
	because these structures only work as handlers.

	data which is read and written into these objects
	will immediately be written into binary files (for exporting)
	or be fed to other objects (for importing)

	these objects then will be removed
	as well as their memory allocation will be freed
*/

struct HackingState {
	int h, w;	// boardgame size
	int y, x;	// cursor
	char board[HackingParam::GameLen];
	char bgUrl[HackingParam::PathLen];

	char __padding[HackingParam::Padding];
};

struct HackingDate {
	int dd, mm, yy;
};

struct HackingRecord {
	HackingDate date;
	int pts;
	
	char __padding[HackingParam::Padding];
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
