
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Mon Apr  3 14:10:46 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

/**
 * @ template stuffs
 * */
#define PADDING 500
#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100

struct State {
	int p, q;
	int p_, q_;
	char board[BOARDSIZE];
	char file_background[URLSIZE];
	// 500 byte NULL
};

struct Date {
	int dd, mm, yy;
};

struct Record {
	Date date;
	int points;
	// 500 byte NULL
};

struct Savefile {
	char mask;
	char usrn[NAMESIZE];
	char pass[PASSSIZE];
	// 500 byte NULL	<-- may be missing here
	Record record[5]; // List of sorted best records
	State state[5]; // List of save state

	Savefile() {
		mask = 0;
		memset(usrn, 0, sizeof(usrn));
		memset(pass, 0, sizeof(pass));
	}
};

/**
 * @ my stuffs
 * */
string mask(string s, char msk) {
	for (char &c: s) c ^= msk;
	return s;
}

void write() {
	// defaults
	string usrn = "bhthong";
	string pass = "fit@hcmus";

	// usrn & pass
	Savefile save;
	save.mask = 81;	// 51 hex
	const char* m_usrn = mask(usrn, save.mask).c_str();
	const char* m_pass = mask(pass, save.mask).c_str();
	memcpy(save.usrn, m_usrn, sizeof(usrn[0]) * usrn.length());
	memcpy(save.pass, m_pass, sizeof(pass[0]) * pass.length());

	// date
	Date d0 = { 12, 11, 2023 };
	Date d1 = { 23, 10, 2022 };
	Record r0 = { d0, 100000 };
	Record r1 = { d1, 200000 };
	save.record[0] = r0;
	save.record[1] = r1;

	// write
	ofstream fo("hacker.bin", ios::out | ios::binary);
	fo.write((char*) &save, sizeof(Savefile));
	fo.close();
}

void read() {
	Savefile save;

	ifstream fi("hacker.bin", ios::out | ios::binary);
	fi.read((char*) &save, sizeof(Savefile));

	string usrn = save.usrn; usrn = mask(usrn, save.mask);
	string pass = save.pass; pass = mask(pass, save.mask);

	cout << usrn << " " << pass << "\n";
}

int main(int argc, char const *argv[]) {
	// write();
	read();
	return 0;
}
