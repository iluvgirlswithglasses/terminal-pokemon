
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Thu Mar 23 17:14:05 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

/*
@ references: 
	line 53-69: Morgan McGuire "_kbhit() for Linux"
	            https://www.flipcode.com/archives/_kbhit_for_Linux.shtml
*/

#ifndef INPUT_H
#define INPUT_H
// ------------------------------------------------------------

#if _WIN32			// ----------------------------------------

#include <conio.h>
struct Input {
	static char wait_keypress() {
		while (!_kbhit());
		return _getch();
	}
};

#elif __linux__		// ----------------------------------------

#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/select.h>

struct Input {
public:
	static char wait_keypress() {
		while (!_kbhit());
		char c = getchar();
		printf("\b");	// clear the inputted char out of console
		return c;
	}

private:
	static int _kbhit() {
		static const int STDIN = 0;
		static bool initialized = false;

		if (!initialized) {
			// Use termios to turn off line buffering
			termios term;
			tcgetattr(STDIN, &term);
			term.c_lflag &= ~ICANON;
			tcsetattr(STDIN, TCSANOW, &term);
			setbuf(stdin, NULL);
			initialized = true;
		}
		int bytesWaiting;
		ioctl(STDIN, FIONREAD, &bytesWaiting);
		return bytesWaiting;
	}
};

#endif	// _WIN32 __linux__

#endif	// INPUT_H
