
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
Gameboard::Gameboard(char** map, int _h, int _w) {
	h = _h + 2;	// padding for tldr
	w = _w + 2;

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
	first = mat[1][1];
	// the mat is not needed anymore, return h & w to normal
	h -= 2;
	w -= 2;
	remaining = (h - 2) * (w - 2);	// the input data has 1 cell padding
}

Gameboard::~Gameboard() {
	dfs_remove(first);
}

void Gameboard::dfs_remove(Node* node) {
	if (node == nullptr) return;
	dfs_remove(node->adj[R]);
	dfs_remove(node->adj[D]);
	delete node;
	node = nullptr;
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
	to_array_dfs(ans, first, 0, 0);
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			// some slided tiles results in nullptr
			if (ans[y][x] == '\0') ans[y][x] = EmptyCell;
	return ans;
}

void Gameboard::to_array_dfs(char** ans, Node* node, int y, int x) {
	// if null node / cell is already assigned --> break
	if (node == nullptr || ans[y][x] != '\0') return;
	ans[y][x] = node->val;
	to_array_dfs(ans, node->adj[R], y, x+1);
	to_array_dfs(ans, node->adj[D], y+1, x);
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

void Gameboard::slide_dfs(const int y, const int x, const int ori, const int top, const int dwn) {
	Node* erased = get_node(y, x);
	Node* pre = erased->adj[REV[ori]];
	Node* nxt = erased->adj[ori];
	slide_dfs(nxt, ori, top, dwn, erased->adj[top], erased->adj[dwn]);
	if (pre != nullptr) pre->adj[ori] = nxt;
	if (nxt != nullptr) nxt->adj[REV[ori]] = pre;
	delete erased;
	erased = nullptr;
}

void Gameboard::slide_lft(int y, int x) { slide_dfs(y, x, R, T, D); }
void Gameboard::slide_rgt(int y, int x) { slide_dfs(y, x, L, T, D); }
void Gameboard::slide_top(int y, int x) { slide_dfs(y, x, D, L, R); }
void Gameboard::slide_dwn(int y, int x) { slide_dfs(y, x, T, L, R); }

/**
 * @ 2d linkedlist utils
 * */
void Gameboard::push(Node* node, int ori, int val) {
	Node* next = new Node(val);
	node->adj[ori] = next;
	next->adj[REV[ori]] = node;
}

Node* Gameboard::get_node(int y, int x) {
	Node* ans = first;
	while (y--) ans = ans->adj[D];
	while (x--) ans = ans->adj[R];
	return ans;
}
