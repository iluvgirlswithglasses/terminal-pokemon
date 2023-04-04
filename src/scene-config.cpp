
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Tue Apr  4 13:54:04 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "scene-config.h"

#if __linux__	// ------------------------------------------------------------------------
#include <chrono>
#include <thread>
void SceneConfig::start(Renderer* rdr) {
	static constexpr int 
		h = Param::ScreenHeight, w = Param::ScreenWidth;
	static constexpr char 
		note1[] = "please adjust your console so that you see a 100x40 rectangle",
		note2[] = "then you may press any key to continue";

	rdr->clrmap();
	// borders
	for (int x = 0; x < w; x++)
		rdr->map[0][x] = rdr->map[h-1][x] = '-';
	for (int y = 0; y < h; y++)
		rdr->map[y][0] = rdr->map[y][w-1] = '|';
	rdr->map[0][0] = rdr->map[h-1][0] = rdr->map[0][w-1] = rdr->map[h-1][w-1] = '+';
	// note
	rdr->wrtext(h - 5, 31, note1);
	rdr->wrtext(h - 3, 31+23, note2);

	// render
	while (!Input::_kbhit()) {
		rdr->render();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

#elif _WIN32	// ------------------------------------------------------------------------
#include <windows.h>
#include "windows-console.h"
#include "color.h"
void SceneConfig::start(Renderer* rdr) {
	static constexpr int 
		h = Param::ScreenHeight, w = Param::ScreenWidth;
	static constexpr char 
		note1[] = "please adjust your console so that you see a 100x40 rectangle",
		note2[] = "then you may press any key to continue";
	static constexpr int
		noteLft = 31, noteDif = 23;

	// some notes for windows user
	// because windows' rendering is so weird it mixes up rows and cols
	// that the notes in renderer can't even show up properly

	Color::setft(Color::Cyan, Color::Regular);
	printf("\n\nthis note is for windows user only:\n");
	Color::reset();
	printf("you may now enter the console adjusting scene\n");
	printf("once you are there, ");
	printf("%s\n", note1);
	printf("%s\n", note2);
	Color::setft(Color::Green, Color::Regular);
	printf("press any key to start adjusting your console...");
	Color::reset();
	Input::wait_keypress();

	rdr->clrmap();
	// borders
	for (int x = 0; x < w; x++)
		rdr->map[0][x] = rdr->map[h-1][x] = '-';
	for (int y = 0; y < h; y++)
		rdr->map[y][0] = rdr->map[y][w-1] = '|';
	rdr->map[0][0] = rdr->map[h-1][0] = rdr->map[0][w-1] = rdr->map[h-1][w-1] = '+';
	// note
	rdr->wrtext(h - 5, noteLft, note1);
	rdr->wrtext(h - 3, noteLft + noteDif, note2);

	// render
	rdr->render();
	while (!_kbhit()) {
		for (int x = 0; x < w; x++) {
			WindowsConsole::plot_pixel(rdr, 0, x);
			WindowsConsole::plot_pixel(rdr, h-1, x);
		}
		for (int y = 0; y < h; y++) {
			WindowsConsole::plot_pixel(rdr, y, 0);
			WindowsConsole::plot_pixel(rdr, y, w-1);
		}
		for (int x = noteLft; x < w; x++) {
			WindowsConsole::plot_pixel(rdr, h - 5, x);
			WindowsConsole::plot_pixel(rdr, h - 3, x);
		}
		Sleep(500);
		rdr->clrscr();
	}
}

#endif			// ------------------------------------------------------------------------
