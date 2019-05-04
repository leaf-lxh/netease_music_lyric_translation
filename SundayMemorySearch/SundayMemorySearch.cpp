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

		std::wstring window_name, class_name;
		/*
		std::wcout << "WindowName >>";
		
		std::getline(std::wcin, window_name);
		//std::cin.ignore
		std::wcout << "WindowClassName >>";
		std::getline(std::wcin, class_name);
		*/
		window_name = L"桌面歌词";
		class_name = L"";
		MemorySearchx64 s;
		std::vector<DWORD_PTR> PID = s.GetPIDByWindow(window_name, class_name);
		if (PID.size() != 0)
		{
			std::wcout << s.GetModuleBaseAddress(PID[0], L"cloudmusic.dll");
		}

		std::cin.get();
	}
	
    return 0;
}

