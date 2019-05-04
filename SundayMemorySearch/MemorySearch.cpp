#include "stdafx.h"
#include "MemorySearch.h"

#include <TlHelp32.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lparam)
{
	//整理传入的参数
	LONG_PTR *ptr = (LONG_PTR*)lparam;
	std::string *swindowName = (std::string *)ptr[0];
	std::string *swindowClassName = (std::string *)ptr[1];
	std::vector<DWORD_PTR> *PID = (std::vector<DWORD_PTR> *)ptr[2];

	//对窗口标题和类名进行判断
	char *windowName = new char[swindowName->size() + 2];
	char *windowClassName = new char[swindowClassName->size() + 2];

	memset(windowName, 0, swindowName->size() + 2);
	memset(windowName, 0, swindowName->size() + 2);

	if (swindowName->compare("") != 0)
	{
		GetWindowTextA(hwnd, windowName, swindowName->size() + 1);
		if (swindowName->compare(windowName) != 0)
		{
			return TRUE;
		}
	}

	if (swindowClassName->compare("") != 0)
	{
		GetClassNameA(hwnd, windowClassName, swindowClassName->size() + 1);
		if (swindowClassName->compare(windowClassName) != 0)
		{
			return TRUE;
		}
	}
	
	//向结果容器添加符合条件的进程标识符
	DWORD pid = 0;
	if (!GetWindowThreadProcessId(hwnd, &pid))
	{
		return TRUE;
	}

	if (pid != 0)
	{
		PID->push_back(pid);
	}
	
	delete[] windowName;
	delete[] windowClassName;

	return TRUE;
}

std::vector<DWORD_PTR> MemorySearchx64::GetPidByWindow(std::string windowName, std::string windowClassName)
{
	std::vector<DWORD_PTR> PID;
	LONG_PTR ptr[3] = { (LONG_PTR)&windowName, (LONG_PTR)&windowClassName, (LONG_PTR)&PID };

	EnumWindows(&EnumWindowsProc, (LPARAM)ptr);

	return PID;
}

std::vector<DWORD_PTR> MemorySearchx64::GetPidByProcessName(std::string processName)
{
	EnumProcess
	return std::vector<DWORD_PTR>();
}

DWORD_PTR MemorySearchx64::GetPidByCursorPos(POINT pos)
{
	return DWORD_PTR();
}

std::vector<DWORD_PTR> MemorySearchx64::SearchArray(DWORD_PTR startAddress, DWORD_PTR stopAddress, std::vector<char> pattern)
{
	return std::vector<DWORD_PTR>();
}
