
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Apr  3 13:32:01 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <map>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
#define st first
#define nd second
#define all(c) c.begin(), c.end()

map<char, int> m = {
	{'0', 0 },
	{'1', 1 },
	{'2', 2 },
	{'3', 3 },
	{'4', 4 },
	{'5', 5 },
	{'6', 6 },
	{'7', 7 },
	{'8', 8 },
	{'9', 9 },
	{'a', 10 },
	{'b', 11 },
	{'c', 12 },
	{'d', 13 },
	{'e', 14 },
	{'f', 15 },
};

int toDec(string &s) {
	int ans = 0;
	for (int i = 0; i < s.length(); i++) {
		ans = ans * 16 + m[s[i]];
	}
	return ans;
}

void parseChar() {
	string _msk; cin >> _msk;
	int msk = toDec(_msk);
	while (true) {
		string s; cin >> s;
		int cr = toDec(s);
		char c = cr ^ msk;
		cout << c << "\n";
	}
}

void parseNum() {
	while (true) {
		string s; cin >> s;
		cout << toDec(s) << "\n";
	}
}

int main() {
	// ios_base::sync_with_stdio(false); cin.tie(0);
	parseNum();
	return 0;
}
