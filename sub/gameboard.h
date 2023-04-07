
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

	static const int T = 0, L = 1, D = 2, R = 3;
	static const int REV[4];	// REV[ T/L/D/R ] = D/R/T/L

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

	/** @ tile slidings */
	void slide_lft(int y, int x);
	void slide_rgt(int y, int x);
	void slide_top(int y, int x);
	void slide_dwn(int y, int x);
	
	void slide_dfs(const int y, const int x, const int ori, const int top, const int dwn);
	void slide_dfs(Node* n, const int ori, const int top, const int dwn, Node* ntop, Node* ndwn);

	/** @ 2d-linkedlist utils */
	void push(Node* node, int ori, int val);	// push a new node
	Node* get_node(int y, int x);				// get (y, x) node
	char get_value(int y, int x) { return get_node(y, x)->val; }
};

#endif	// GAMEBOARD_H
