
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Mar 21 12:48:19 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "linked-list.h"

template<typename T> T LinkedList<T>::get(int i) {
	typename Deque<T>::Node* cr = this->first;
	while (i--) cr = cr->r;
	return cr->v;
}

template<typename T> T LinkedList<T>::remove(int i) {
	if (i == 0) return this->pop_front();
	if (i == this->count() - 1) return this->pop_back();
	typename Deque<T>::Node* cr = this->first;
	while (i--) cr = cr->r;
	return remove_node(cr);
}

template<typename T> bool LinkedList<T>::remove_value(T v) {
	typename Deque<T>::Node* cr = this->first;
	for (int i = 0; i < this->count(); i++, cr = cr->r) {
		if (v == cr->v) {
			remove_node(cr);
			return true;
		}
	}
	return true;
}

template<typename T> T LinkedList<T>::remove_node(typename Deque<T>::Node* n) {
	// n->l and n->r must be non-null
	typename Deque<T>::Node* l = n->l;
	typename Deque<T>::Node* r = n->r;
	l->r = r;
	r->l = l;
	(this->m_count)--;

	T val = n->v;
	delete n;
	return val;
}
