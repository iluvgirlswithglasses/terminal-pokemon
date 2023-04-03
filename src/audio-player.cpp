
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

const std::string AudioPlayer::AudioDirectory = "sfx/";

#if __linux__	// --------------------------------------------
void AudioPlayer::play(const char* _f) {}

#elif _WIN32	// --------------------------------------------
#include <windows.h>
void AudioPlayer::play(const char* _f) {
	std::string f = _f;
	f = AudioDirectory + f;
	PlaySound(TEXT(f.c_str()), NULL, SND_FILENAME | SND_ASYNC);
}

#endif			// --------------------------------------------
