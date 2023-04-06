
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Thu Apr  6 17:50:29 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H
// ------------------------------------------------------------

struct Node {
	static const int T = 0, L = 1, D = 2, R = 3;
	static const int REV[4];	// REV[ T/L/D/R ] = D/R/T/L

	char val;
	Node* adj[4];	// adj[ T/L/D/R ] = top/left/down/right adjacent node

	Node() { Node(0); }

	Node(char v) {
		val = v;
		for (int i = 0; i < 4; i++) adj[i] = nullptr;
	}
};

struct Gameboard {
	static constexpr char EmptyCell = ' ';		// empty cell is marked as '\32'

	/** @ properties */
	Node* first = nullptr;
	int h, w;		// size of the map
	int remaining;	// remaining tiles

	/** @ constructors & deconstructors */
	Gameboard(char** map, int h, int w);		// load game from a 2d game map
	~Gameboard();
	void dfs_remove(Node* n);

	/** @ linkedlist to 2d-array */
	char** to_array();
	void to_array_dfs(char** ans, Node* node, int y, int x);

	/** @ 2d-linkedlist utils */
	void push(Node* node, int ori, int val);	// push a new node
};

#endif	// GAMEBOARD_H
