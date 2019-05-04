// SundayMemorySearch.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MemorySearch.h"

#include <iostream>
#include <string>
#include <vector>


int main()
{
	while (true)
	{

		std::string window_name, class_name;
		std::cout << "WindowName >>";
		std::getline(std::cin, window_name);
		//std::cin.ignore
		std::cout << "WindowClassName >>";
		std::getline(std::cin, class_name);

		MemorySearchx64 s;
		for (auto &i : s.GetPidByWindow(window_name, class_name))
		{
			std::cout << i << std::endl;
		}

		
		std::cin.get();
	}
	
    return 0;
}

