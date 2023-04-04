
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 13:44:06 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef SCENE_CONFIG_H
#define SCENE_CONFIG_H
// ------------------------------------------------------------

#include <cstdio>
#include "param.h"
#include "renderer.h"
#include "input.h"

struct SceneConfig {
	// something that helps the user to adjust their console
	// consumes a while() thread
	static void start(Renderer* rdr);
};

#endif	// SCENE_CONFIG_H
