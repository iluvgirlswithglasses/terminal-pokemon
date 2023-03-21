
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Mar 21 20:33:28 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "gameboard-logic-easy.h"

/**
 * @ initializer & deconstructor
 * */
GameboardLogicEasy::GameboardLogicEasy(uint8_t _h, uint8_t _w, uint8_t** _map) {
	h = _h;
	w = _w;
	map = _map;

	vst = new uint8_t*[h];
	for (int y = 0; y < h; y++)
		vst[y] = new uint8_t[w];

	trace = new uint32_t*[h];
	for (int y = 0; y < h; y++)
		trace[y] = new uint32_t[w];
}

GameboardLogicEasy::~GameboardLogicEasy() {
	for (int y = 0; y < h; y++) {
		delete[] vst[y];
		delete[] trace[y];
	}
	delete[] vst;
	delete[] trace;
}

/**
 * @ tracing DFS
 * */
Deque<uint16_t> GameboardLogicEasy::get_path(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
	Deque<uint16_t> ans;
	return ans;
}

void GameboardLogicEasy::traceDFS(Deque<uint16_t> &q, uint8_t dy, uint8_t dx, uint8_t y, uint8_t x) {

}

/**
 * @ BFS
 * */
bool GameboardLogicEasy::validate(uint8_t y0, uint8_t x0, uint8_t y1, uint8_t x1) {
	return false;
}

uint32_t GameboardLogicEasy::suggest() {
	return 0;
}

void GameboardLogicEasy::reset_vst() {

}

uint16_t GameboardLogicEasy::BFS(uint8_t y0, uint8_t x0, bool fixed, uint8_t y1, uint8_t x1) {
	return 0;
}
