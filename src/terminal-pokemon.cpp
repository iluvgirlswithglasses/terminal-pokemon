
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Mar 20 08:08:34 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include <cstdio>
#include <cstring>

#include <iostream>

#include "deque.cpp"

int main() {
	Deque<int> q;
	while (true) {
		char operation; std::cin >> operation;
		int v;

		switch (operation) {
		case 'b':
			std::cin >> v;
			q.push_back(v);
			break;
		case 'f':
			std::cin >> v;
			q.push_front(v);
			break;
		case 'r':
			q.pop_back();
			break;
		case 'l':
			q.pop_front();
			break;
		case 'd':
			q.deb();
			break;
		}
	}
	return 0;
}
