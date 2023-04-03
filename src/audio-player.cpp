
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Apr  3 10:10:46 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "audio-player.h"

#if __linux__	// --------------------------------------------
void AudioPlayer::play(int hz, int t) {}

#elif _WIN32	// --------------------------------------------
#include <windows.h>
void AudioPlayer::play(int hz, int t) {
	Beep(hz, t);
}

#endif			// --------------------------------------------
