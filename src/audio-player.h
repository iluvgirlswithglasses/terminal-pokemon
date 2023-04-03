
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Apr  3 09:15:17 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H
// ------------------------------------------------------------

/*
about this:
    plays audio files asynchronously
    currently supports windows only

    tbh i'd prefer my console game to be quite
    or just produces "bip bip" sounds on errors only
    so I wouldn't implement this on linux regardless
*/

#include <string>

struct AudioPlayer {
    static const std::string AudioDirectory;

    static void play(const char* f);
};

#endif	// AUDIO_PLAYER_H
