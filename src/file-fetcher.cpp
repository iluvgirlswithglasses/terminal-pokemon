
/*
author: 	iluvgirlswithglasses 
github: 	https://github.com/iluvgirlswithglasses 
created:	Sun Apr  2 21:54:15 2023
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
BTW I use Arch
*/

#include "file-fetcher.h"

Array<std::string> FileFetcher::ls(std::string d) {
	Deque<std::string> q;
	for (const auto& entry: std::filesystem::directory_iterator(d)) {
		q.push_back(entry.path());
	}
	Array<std::string> ans(q.count());
	for (int i = 0; i < ans.len; i++)
		ans[i] = q.pop_front();
	return ans;
}
