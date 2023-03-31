
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Fri Mar 31 11:08:31 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "array.h"

template<typename T> Array<T>::Array(int n) {
	arr = new T[n];
	len = n;
}

template<typename T> Array<T>::~Array() {
	delete[] arr;
}

// ------------------------------------------------------------------
// @ Explicit instantiations ----------------------------------------
template struct Array<uint8_t>;
template struct Array<uint16_t>;
template struct Array<uint32_t>;
template struct Array<int>;
// ------------------------------------------------------------------
