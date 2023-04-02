
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Fri Mar 31 11:02:10 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef ARRAY_H
#define ARRAY_H
// ------------------------------------------------------------

/*
@ about this:
	I thought I could complete the project using only linked list
	but GOD I HATE LINKED LIST
*/

template<typename T> struct Array {
public:
	int len;
	T* arr;

	Array(int len);
	~Array();

	T operator [](int i) const { return arr[i]; }
    T &operator [](int i) { return arr[i]; }
};

#endif	// ARRAY_H
