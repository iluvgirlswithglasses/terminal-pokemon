
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Mar 21 12:48:20 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
// ------------------------------------------------------------

/*
@ about this:
	an extension from `deque.h`
	was created to solve the difficulty special requirement

	note that this object does not check index out of bound
	please use with cares
*/

#include "deque.h"

template<typename T> class LinkedList: public Deque<T> {
public:
	T get(int i);		// gets the `i-th` element
	T remove(int i);	// removes the `i-th` element

	// removes the first item with value `v`
	// if found none, returns false
	bool remove_value(T v);

protected:
	// only removes middle nodes
	// the "typename" keyword is there to treat `Deque<T>::Node` as a type
	T remove_node(typename Deque<T>::Node* n);
};

#endif	// LINKED_LIST_H
