
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 21:33:13 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef QMATH_H
#define QMATH_H
// ------------------------------------------------------------

#include "random"

struct Qmath {
	// actually its bubble sort
	static void quick_sort(int* a, int l, int r) {
		for (int i = l; i < r; i++)
			for (int j = l; j < r-1; j++)
				if (a[j] > a[j+1]) std::swap(a[j], a[j+1]);
	}
};

#endif	// QMATH_H
