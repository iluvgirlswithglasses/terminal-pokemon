
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Thu Apr  6 19:33:49 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#ifndef SAVE_LOADER_H
#define SAVE_LOADER_H
// ------------------------------------------------------------

struct SaveLoader {
public:
	static constexpr int H = 6, W = 6;

	static void del_map(char** map) {
		for (int y = 0; y < H; y++) delete[] map[y];
		delete[] map;
	}

	char** get_map() {
		if (map == nullptr) {
			map = new char*[H] {
				new char[W] { ' ', ' ', ' ', ' ', ' ', ' ', },
				new char[W] { ' ', 'A', 'N', 'K', 'K', ' ', },
				new char[W] { ' ', 'A', 'O', 'H', 'A', ' ', },
				new char[W] { ' ', 'M', 'H', 'N', 'A', ' ', },
				new char[W] { ' ', 'G', 'O', 'G', 'M', ' ', },
				new char[W] { ' ', ' ', ' ', ' ', ' ', ' ', },
			};
		}
		return map;
	}

private:
	char** map = nullptr;
};

#endif	// SAVE_LOADER_H
