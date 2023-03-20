
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

#include <cstdint>

template <typename T> struct Deque {

public:
	/**
	 * @ this node is used in this deque only
	 * */
	struct Node {
		T     val;	// value of this node
		Node* l;	// the left node
		Node* r;	// the right node

		Node(T _val, Node* _l, Node* _r) {
			val = _val;
			l = _l;
			r = _r;
		}
	};

	/**
	 * @ constructor
	 * */
	Deque() {
		m_count = 0;
		first = nullptr;
		last = nullptr;
	}

	/**
	 * @ getters
	 * */
	int count() { return m_count; }
	T front() { return first->val; }
	T back() { return last->val; }

	/**
	 * @ inserting
	 * */
	void push_front(T v) {
		Node cr(v, nullptr, first);
		if (++m_count == 1)
			last = &cr;
		else
			first->l = &cr;
		first = cr;
	}

	void push_back(T v) {
		Node cr(v, last, nullptr);
		if (++m_count == 1)
			first = &cr;
		else
			last->r = &cr;
		last = cr;
	}

	/**
	 * @ popping
	 * 
	 * throws an error if `count() == 0` when called
	 * */
	T pop_front() {
		T res = front();
		Node* cr = first, nxt = first->r;
		
		if (--m_count == 0) {
			first = last = nullptr;
		} else {
			first = nxt;
			first->l = nullptr;
		}
		delete cr;
		return res;
	}

	T pop_back() {
		T res = back();
		Node* cr = last, nxt = last->l;

		if (--m_count == 0) {
			first = last = nullptr;
		} else {
			last = nxt;
			last->r = nullptr;
		}
		delete cr;
		return res;
	}

private:
	int m_count;
	Node* first;
	Node* last;
};