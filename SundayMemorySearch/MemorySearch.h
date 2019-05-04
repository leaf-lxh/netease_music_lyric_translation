#pragma once

#include "sunday.h"
#include <Windows.h>

#include <vector>

/*!
提供了搜索内存的方法，使用Sunday字符串匹配算法
同时也提供了通过窗口特征、进程名称，鼠标位置获取进程ID的方法
32位和64位系统均支持，开启64位支持需要用x64方式编译
类名：MemorySearchx64
基类：SundaySearch
*/
class MemorySearchx64 : public SundaySearch
{
public:
	/*!
	根据窗口名获取创建该窗口的进程的进程标识符
	参数：windowName      | 窗口标题，如不需要判断，传递空字符串
	参数：windowClassName | 窗口类名，如不需要判断，传递空字符串
	返回：进程标识符，查找失败vector.size=0
	*/
	std::vector<DWORD_PTR> GetPidByWindow(std::string windowName, std::string windowClassName);

	/*!
	根据进程进程名称返回进程标识符
	参数：processName | 任务管理器能看到的进程名称，如abc.exe
	返回：进程标识符，查找失败vector.size=0
	*/
	std::vector<DWORD_PTR> GetPidByProcessName(std::string processName);

	/*!
	获取鼠标位置下的窗口
	参数：pos | 鼠标指针的坐标
	返回：进程标识符，查找失败返回NULL
	*/
	DWORD_PTR GetPidByCursorPos(POINT pos);

	/*!
	根据pattern搜索内存，返回符合条件的起始内存地址
	参数：startAddress | 搜索的起始内存地址
	参数：stopAddress  | 搜索的终止内存地址
	参数：pattern      | 欲搜索的特征
	返回：符合条件的内存地址，查询失败vector.size=0
	*/
	std::vector<DWORD_PTR> SearchArray(DWORD_PTR startAddress, DWORD_PTR stopAddress, std::vector<char> pattern);
};