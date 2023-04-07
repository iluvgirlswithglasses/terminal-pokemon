
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Thu Apr  6 17:58:02 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "gameboard.h"

const int Gameboard::REV[4] = { Gameboard::D, Gameboard::R, Gameboard::T, Gameboard::L };

/**
 * @ constructors & deconstructors
 * */
Gameboard::Gameboard(char** map, int _h, int _w, char _ori) {
	h = _h + 2;	// padding for tldr
	w = _w + 2;
	ori = _ori;

	/** @ build a 2d array first, then the linked list later */
	Node*** mat = new Node**[h];
	for (int y = 0; y < h; y++)
		mat[y] = new Node*[w];
	// first & last row
	for (int x = 0; x < w; x++)
		mat[0][x] = mat[h-1][x] = nullptr;
	// the rest
	for (int y = 1; y < h-1; y++) {
		mat[y][0] = mat[y][w-1] = nullptr;
		for (int x = 1; x < w-1; x++)
			mat[y][x] = new Node(map[y-1][x-1]);
	}
	// link all nodes together
	for (int y = 1; y < h-1; y++) {
		for (int x = 1; x < w-1; x++) {
			Node* n = mat[y][x];
			n->adj[T] = mat[y-1][x];
			n->adj[L] = mat[y][x-1];
			n->adj[D] = mat[y+1][x];
			n->adj[R] = mat[y][x+1];
		}
	}
	switch (ori) {
	case 't': case 'l':
		first = mat[1][1]; break;
	case 'd': case 'r':
		first = mat[h-2][w-2]; break;
	}
	// the mat is not needed anymore, return h & w to normal
	h -= 2;
	w -= 2;
	remaining = (h - 2) * (w - 2);	// the input data has 1 cell padding
}

/**
 * @ convert to 2d array
 * */
char** Gameboard::to_array() {
	char** ans = new char*[h];
	for (int y = 0; y < h; y++) {
		ans[y] = new char[w];
		for (int x = 0; x < w; x++) ans[y][x] = '\0';
	}
	switch (ori) {
	case 't': case 'l':
		to_array_dfs(ans, first, 0, 0, D, R, 1, 1); break;
	case 'd': case 'r':
		to_array_dfs(ans, first, h-1, w-1, T, L, -1, -1); break;
	}
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			// some slided tiles results in nullptr
			if (ans[y][x] == '\0') ans[y][x] = EmptyCell;
	return ans;
}

void Gameboard::to_array_dfs(char** ans, Node* node, int y, int x, int yori, int xori, int yinc, int xinc) {
	// if null node / cell is already assigned --> break
	if (node == nullptr || ans[y][x] != '\0') return;
	ans[y][x] = node->val;
	to_array_dfs(ans, node->adj[yori], y + yinc, x, yori, xori, yinc, xinc);
	to_array_dfs(ans, node->adj[xori], y, x + xinc, yori, xori, yinc, xinc);
}

/**
 * @ tiles sliding
 * 
 * The DFS flow is REVERSED compared to optical vision.
 * 
 * Therefore, to make tiles to appear sliding right,
 * DFS to the left.
 * 
 * The same goes to all other orientations.
 * */
void Gameboard::slide_dfs(Node* n, const int ori, const int top, const int dwn, Node* ntop, Node* ndwn) {
	if (ntop != nullptr) ntop->adj[dwn] = n;
	if (ndwn != nullptr) ndwn->adj[top] = n;
	if (n == nullptr) return;
	slide_dfs(n->adj[ori], ori, top, dwn, n->adj[top], n->adj[dwn]);
	n->adj[top] = ntop;
	n->adj[dwn] = ndwn;
}

void Gameboard::slide_dfs(Node* erased, const int ori, const int top, const int dwn) {
	Node* pre = erased->adj[REV[ori]];
	Node* nxt = erased->adj[ori];
	slide_dfs(nxt, ori, top, dwn, erased->adj[top], erased->adj[dwn]);
	if (pre != nullptr) pre->adj[ori] = nxt;
	if (nxt != nullptr) nxt->adj[REV[ori]] = pre;
	delete erased;
	erased = nullptr;
}

void Gameboard::slide_dfs(int y0, int x0, int y1, int x1, int ori, int top, int dwn) {
	Node* a = get_node(y0, x0);
	Node* b = get_node(y1, x1);	// location might be change, but the node doesnt
	slide_dfs(a, ori, top, dwn);
	slide_dfs(b, ori, top, dwn);
}

void Gameboard::slide_lft(int y0, int x0, int y1, int x1) { slide_dfs(y0, x0, y1, x1, R, T, D); }
void Gameboard::slide_rgt(int y0, int x0, int y1, int x1) { slide_dfs(y0, x0, y1, x1, L, T, D); }
void Gameboard::slide_top(int y0, int x0, int y1, int x1) { slide_dfs(y0, x0, y1, x1, D, L, R); }
void Gameboard::slide_dwn(int y0, int x0, int y1, int x1) { slide_dfs(y0, x0, y1, x1, T, L, R); }

/**
 * @ 2d linkedlist utils
 * */

Node* Gameboard::get_node(int y, int x) {
	Node* ans = first;
	switch (ori) {
	case 't':
		while (ans != nullptr && x--) ans = ans->adj[R];	// Ox first
		while (ans != nullptr && y--) ans = ans->adj[D];	// Oy second
		return ans;
	case 'l':
		while (ans != nullptr && y--) ans = ans->adj[D];	// Oy first
		while (ans != nullptr && x--) ans = ans->adj[R];	// Ox second
		return ans;
	case 'd':
		y = h - y - 1;
		x = w - x - 1;
		while (ans != nullptr && x--) ans = ans->adj[L];	// Ox first
		while (ans != nullptr && y--) ans = ans->adj[T];	// Oy second
		return ans;
	case 'r':
		y = h - y - 1;
		x = w - x - 1;
		while (ans != nullptr && y--) ans = ans->adj[T];	// Oy first
		while (ans != nullptr && x--) ans = ans->adj[L];	// Ox second
		return ans;
	}
	return nullptr;
}

char Gameboard::get_value(int y, int x) {
	Node* n = get_node(y, x);
	if (n == nullptr) return EmptyCell;
	return n->val;
}
