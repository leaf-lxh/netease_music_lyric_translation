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
	src = "123456789";
	sub = "456";

	SundaySearch s;
	std::cout << s.Search(std::vector<char>(src.cbegin(), src.cend()), std::vector<char>(sub.cbegin(), sub.cend()));
}

void fuzzTest()
{
	std::string src, sub;
	src = "AABABBBBCCCC";
	sub = "41 41 41 41 ";
	SundaySearch s;
	std::cout << s.FuzzSearch(std::vector<char>(src.cbegin(), src.cend()), sub);

}
int main()
{
	while (true)
	{

		fuzzTest();
		std::cin.get();
	}
	
    return 0;
}

