
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 12:56:46 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef SCENE_LOGIN_H
#define SCENE_LOGIN_H
// ------------------------------------------------------------

#include "account.h"
#include "color.h"
#include "input.h"
#include <cstdio>

struct SceneLogin {
public:
    // consumes a while() thread
    // creates a login scene
    // thread stops after login/register successfully
    // credentials is then stored at account.h static session
	static Account start();

private:
    static void getpwd(Account& acc);
};

#endif	// SCENE_LOGIN_H
