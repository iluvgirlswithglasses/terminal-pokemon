
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Mar 20 08:08:44 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef DEQUE_H
#define DEQUE_H
// ------------------------------------------------------------

/*
@ about this:
	a very inefficient deque
	implemented via a linked list

note that whenever this deque removes an item,
it will only free that memory cell, 
and it won't change the program's memory allocation

in other words, it wouldn't create any memory leak,
but it wouldn't shrink its RAM usage either.
*/

template<typename T> class Deque {

public:
	/**
	 * @ this node is used in this deque only
	 * */
	struct Node {
		T     val;	// value of this node
		Node* l;	// the left node
		Node* r;	// the right node

		Node(T _val, Node* _l, Node* _r);
	};

	Deque();
	~Deque();

	int count() { return m_count; }		// number of elements
	T front() { return first->val; }	// the first element
	T back() { return last->val; }		// the last element

	void push_front(T v);	// add element to front
	void push_back(T v);	// ........... to back

	T pop_front();			// pop the first element
	T pop_back();			// pop the last

	void clear();			// clear the deque

protected:
	int m_count;
	Node* first;
	Node* last;
};

#endif	// DEQUE_H