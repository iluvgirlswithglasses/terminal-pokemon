
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
	/**
	 * a quick sort implementation
	 * 
	 * my senpai used to implement this in his pascal codes
	 * in competitive programming contests
	 * 
	 * didn't think i've got to use it one day
	 * */
	static void quick_sort(int* a, int l, int r) {
		int i = l, j = r, pivot = a[l + rand() % (r - l)];
		while (i <= j) {
			while (a[i] < pivot) i++;
			while (a[j] > pivot) j--;
			if (i <= j) std::swap(a[i++], a[j--]);
		}
		if (l < j) quick_sort(a, l, j);
		if (i < r) quick_sort(a, i, r);
	}
};

#endif	// QMATH_H
