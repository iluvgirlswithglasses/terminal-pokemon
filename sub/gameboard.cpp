
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

const int Node::REV[4] = { Node::D, Node::R, Node::T, Node::L };

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
			n->adj[Node::T] = mat[y-1][x];
			n->adj[Node::L] = mat[y][x-1];
			n->adj[Node::D] = mat[y+1][x];
			n->adj[Node::R] = mat[y][x+1];
		}
	}
	first = mat[1][1];
	// the mat is not needed anymore, return h & w to normal
	h -= 2;
	w -= 2;
}

Gameboard::~Gameboard() {
	dfs_remove(first);
}

void Gameboard::dfs_remove(Node* node) {
	if (node == nullptr) return;
	dfs_remove(node->adj[Node::R]);
	dfs_remove(node->adj[Node::D]);
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
	return ans;
}

void Gameboard::to_array_dfs(char** ans, Node* node, int y, int x) {
	if (ans[y][x] != '\0') return;	// this cell is already assigned
	ans[y][x] = node->val;
	to_array_dfs(ans, node->adj[Node::R], y, x+1);
	to_array_dfs(ans, node->adj[Node::D], y+1, x);
}

/**
 * @ 2d linkedlist utils
 * */
void Gameboard::push(Node* node, int ori, int val) {
	Node* next = new Node(val);
	node->adj[ori] = next;
	next->adj[Node::REV[ori]] = node;
}
