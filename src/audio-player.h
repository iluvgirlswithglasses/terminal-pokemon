
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

struct AudioPlayer {
public:
    static constexpr int C = 523, D = 587, E = 659, F = 698, G = 784, A = 880, B = 987;

    static void play(int hz, int t);
};

#endif	// AUDIO_PLAYER_H
