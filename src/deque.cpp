
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

#include "deque.h"

template<typename T> Deque<T>::Node::Node(T _val, Node* _l, Node* _r) {
	val = _val;
	l = _l;
	r = _r;
}

template<typename T> Deque<T>::Deque() {
	m_count = 0;
	first = nullptr;
	last = nullptr;
}

template<typename T> Deque<T>::~Deque() {
	clear();
}

template<typename T> void Deque<T>::push_front(T v) {
	Node* cr = new Node(v, nullptr, first);
	if (++m_count == 1)
		last = cr;
	else
		first->l = cr;
	first = cr;
}

template<typename T> void Deque<T>::push_back(T v) {
	Node* cr = new Node(v, last, nullptr);
	if (++m_count == 1)
		first = cr;
	else
		last->r = cr;
	last = cr;
}

template<typename T> T Deque<T>::pop_front() {
	T res = front();
	Node* cr = first;
	Node* nxt = first->r;
	
	if (--m_count == 0) {
		first = last = nullptr;
	} else {
		first = nxt;
		first->l = nullptr;
	}
	delete cr;
	return res;
}

template<typename T> T Deque<T>::pop_back() {
	T res = back();
	Node* cr = last;
	Node* nxt = last->l;

	if (--m_count == 0) {
		first = last = nullptr;
	} else {
		last = nxt;
		last->r = nullptr;
	}
	delete cr;
	return res;
}

template<typename T> void Deque<T>::clear() {
	int iterations = m_count;
	while (iterations--) pop_back();
	m_count = 0;
}
