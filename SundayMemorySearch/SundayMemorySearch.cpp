// SundayMemorySearch.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MemorySearch.h"

#include <iostream>
#include <string>
#include <vector>

void testSearch()
{
	std::string src, sub;
	src = "1112301231";
	sub = "1231";

	SundaySearch s;
	std::cout << s.Search(std::vector<char>(src.cbegin(), src.cend()), std::vector<char>(sub.cbegin(), sub.cend()));
}

int main()
{
	while (true)
	{

		testSearch();
		std::cin.get();
	}
	
    return 0;
}

