
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Apr  3 14:47:42 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef HACKING_PARAM_H
#define HACKING_PARAM_H
// ------------------------------------------------------------

/*
@ about this:
	parameters for hacking template
	as required in project statement
*/

struct HackingParam {
	static constexpr int 
		Padding = 500,
		UsrnLen = 50,
		PassLen = 50,
		GameLen = 999,
		PathLen = 100,
		SaveLim = 5;
};

#endif	// HACKING_PARAM_H
