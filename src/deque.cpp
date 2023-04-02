
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

template<typename T> Deque<T> Deque<T>::clone() {
	Deque<T> ans;
	Node* cr = first;
	do {
		ans.push_back(cr->val);
		cr = cr->r;
	} while (cr != nullptr);
	return ans;
}

/**
 * @ linked list functions
 * 
 * linked list is ineffective, and so are the following functions
 * avoid using those unless it's required in the project statement
 * */
template<typename T> T Deque<T>::get_index(int i) {
	// assert i < m_count
	Node* cr = first;
	while (i--) cr = cr->r;
	return cr->val;
}

template<typename T> T Deque<T>::remove_index(int i) {
	// assert i < m_count
	if (i == 0) return pop_front();
	if (i == m_count - 1) return pop_back();
	Node* cr = first;
	while (i--) cr = cr->r;
	return remove_node(cr);
}

template<typename T> bool Deque<T>::remove_value(T v) {
	int i = 0;
	Node* cr = first;
	for (; i < m_count; i++, cr = cr->r) {
		if (cr->val == v) break;
	}
	if (i == 0) {
		pop_front();
		return true;
	}
	if (i == m_count - 1) {
		pop_back();
		return true;
	}
	if (0 < i && i < m_count) {
		remove_node(cr);
		return true;
	}
	return false;
}

template<typename T> T Deque<T>::remove_node(Node* n) {
	// assert n->l and n->r are not null
	Node* l = n->l;
	Node* r = n->r;
	l->r = r;
	r->l = l;
	m_count--;

	T val = n->val;
	delete n;
	return val;
}


// ------------------------------------------------------------------
// @ Explicit instantiations ----------------------------------------
#include <cstdint>
#include <string>

template struct Deque<uint8_t>;
template struct Deque<uint16_t>;
template struct Deque<uint32_t>;
template struct Deque<int>;
template struct Deque<std::string>;
// ------------------------------------------------------------------
