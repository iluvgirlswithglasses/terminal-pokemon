
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

#if __linux__	// ------------------------------------------------------------
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

#elif _WIN32	// ------------------------------------------------------------
/*
provide a "ls" command on Windows
make sure that `d` has a `/` as suffix
because f windows
btw windows doesn't even bother to hide `.` and `..`

references:
	https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
*/
Array<std::string> FileFetcher::ls(std::string d) {
	Deque<std::string> q;

	DIR *dir;
	struct dirent* ent;
	if ((dir = opendir(d.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			std::string s = ent->d_name;
			if (s != "." && s != "..") q.push_back(d + s);
		}
		closedir(dir);
	}

	Array<std::string> ans(q.count());
	for (int i = 0; i < ans.len; i++)
		ans[i] = q.pop_front();
	return ans;
}

#endif			// ------------------------------------------------------------
