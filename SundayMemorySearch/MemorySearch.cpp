#include "stdafx.h"
#include "MemorySearch.h"

#include <TlHelp32.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lparam)
{
	//整理传入的参数
	LONG_PTR *ptr = (LONG_PTR*)lparam;
	std::wstring *swindowName = (std::wstring *)ptr[0];
	std::wstring *swindowClassName = (std::wstring *)ptr[1];
	std::vector<DWORD_PTR> *PID = (std::vector<DWORD_PTR> *)ptr[2];

	//对窗口标题和类名进行判断
	wchar_t *windowName = new wchar_t[swindowName->size()*2 + 4];
	wchar_t *windowClassName = new wchar_t[swindowClassName->size()*2 + 4];

	memset(windowName, 0, swindowName->size()*2 + 4);
	memset(windowName, 0, swindowName->size()*2 + 4);

	if (swindowName->compare(L"") != 0)
	{
		GetWindowTextW(hwnd, windowName, swindowName->size() + 1);
		if (swindowName->compare(windowName) != 0)
		{
			return TRUE;
		}
	}

	if (swindowClassName->compare(L"") != 0)
	{
		GetClassNameW(hwnd, windowClassName, swindowClassName->size() + 1);
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

std::vector<DWORD_PTR> MemorySearchx64::GetPIDByWindow(std::wstring windowName, std::wstring windowClassName)
{
	std::vector<DWORD_PTR> PID;
	LONG_PTR ptr[3] = { (LONG_PTR)&windowName, (LONG_PTR)&windowClassName, (LONG_PTR)&PID };

	EnumWindows(&EnumWindowsProc, (LPARAM)ptr);

	return PID;
}

std::vector<DWORD_PTR> MemorySearchx64::GetPIDByProcessName(std::wstring processName)
{
	std::vector<DWORD_PTR> PID;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32W processInfo;
	processInfo.dwSize = sizeof(PROCESSENTRY32W);
	if (!Process32FirstW(snapshot, &processInfo))
	{
		CloseHandle(snapshot);
		return PID;
	}

	std::wstring currentProcName = processInfo.szExeFile;
	currentProcName = currentProcName.substr(currentProcName.rfind(L'\\') + 1);
	if (currentProcName.compare(processName) == 0)
	{
		PID.push_back(processInfo.th32ProcessID);
	}

	while (Process32NextW(snapshot, &processInfo))
	{
		currentProcName = processInfo.szExeFile;
		currentProcName = currentProcName.substr(currentProcName.rfind(L'\\') + 1);
		if (currentProcName.compare(processName) == 0)
		{
			PID.push_back(processInfo.th32ProcessID);
		}
	}

	CloseHandle(snapshot);
	return PID;
}

DWORD_PTR MemorySearchx64::GetPIDByCursorPos(POINT pos)
{
	return DWORD_PTR();
}

HMODULE MemorySearchx64::GetModuleBaseAddress(DWORD_PTR PID, std::wstring moduleName)
{
	HMODULE hModule;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);
	MODULEENTRY32W moduleInfo;
	moduleInfo.dwSize = sizeof(moduleInfo);
	if (!Module32FirstW(snapshot, &moduleInfo))
	{
		CloseHandle(snapshot);
		return NULL;
	}
	
	std::wstring currentModuleName = moduleInfo.szModule;
	if (moduleName.compare(currentModuleName) == 0)
	{
		hModule = moduleInfo.hModule;
		CloseHandle(snapshot);
		return hModule;
	}

	while (Module32NextW(snapshot, &moduleInfo))
	{
		currentModuleName = moduleInfo.szModule;
		if (moduleName.compare(currentModuleName) == 0)
		{
			hModule = moduleInfo.hModule;
			CloseHandle(snapshot);
			return hModule;
		}
	}

	CloseHandle(snapshot);
	return NULL;
}

std::vector<DWORD_PTR> MemorySearchx64::SearchArray(DWORD_PTR processID, DWORD_PTR startAddress, DWORD_PTR stopAddress, std::vector<char> pattern)
{
	std::vector<DWORD_PTR> resultSet;

	DWORD_PTR currentAddress = startAddress;
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, processID);
	
	std::vector<char> memory;
	while (currentAddress + pattern.size() <= stopAddress)
	{
		MEMORY_BASIC_INFORMATION regionInfo = {};

		if (!VirtualQueryEx(hProcess, (LPVOID)currentAddress, &regionInfo, sizeof(MEMORY_BASIC_INFORMATION)))
		{
			break;
		}

		SIZE_T readSize = regionInfo.RegionSize;
		if (currentAddress != (DWORD_PTR)regionInfo.BaseAddress)
		{
			readSize -= currentAddress - (DWORD_PTR)regionInfo.BaseAddress;
		}

		if (currentAddress + readSize > stopAddress)
		{
			readSize = stopAddress - currentAddress;
		}

		if (regionInfo.Protect != PAGE_NOACCESS)
		{
			ReadProcessMemory(hProcess, (LPCVOID)currentAddress, memory.data(), readSize, NULL);
		}
		
		size_t pos = this->Search(memory, pattern);
		if (pos != UINT_MAX)
		{
			resultSet.push_back(currentAddress + pos);
		}
		currentAddress += readSize;

	}
	return resultSet;
}
