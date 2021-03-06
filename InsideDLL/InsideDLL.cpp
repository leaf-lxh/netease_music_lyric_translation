// InsideDLL.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "InsideDLL.h"

#include <wchar.h>
#include <string>
#include <sstream>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
Backend backend;

void Backend::SendLyric(DWORD unicodePTR)
{
	std::wstring str((wchar_t*)unicodePTR);
	std::wstringstream stream;

	stream << L"lyric\r\n" << str << L"\r\n\r\n";

	this->SendData(str);
}

void Backend::SendTranslation(DWORD unicodePTR)
{
	std::wstring str((wchar_t*)unicodePTR);
	std::wstringstream stream;

	stream << L"trans\r\n" << str << L"\r\n\r\n";

	this->SendData(str);
}

void Backend::SendData(std::wstring &data)
{
	WSADATA version;
	WSAStartup(MAKEWORD(2, 2), &version);

	//为了防止程序卡住，使用UDP协议
	SOCKET serverfd = socket(AF_INET, SOCK_DGRAM, 0);

	sockaddr_in serveraddr = {};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = 23000;
	inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);

	sendto(serverfd, (char*)data.c_str(), data.length()*2+2, 0, (sockaddr*)&serveraddr, sizeof(serveraddr));

	closesocket(serverfd);

}

void __declspec(naked) ToUpdateLyricFunction(void)
{
	__asm
	{
		push eax
		jmp [backend.update_lyric_function + 1]
	}
}

void __declspec(naked) ToUpdateTranslationFunction(void)
{
	__asm
	{
		push eax
		jmp [backend.update_translation_function + 1]
	}
}

LONG Handler(PEXCEPTION_POINTERS context)
{
	if (context->ExceptionRecord->ExceptionAddress == (PVOID)backend.update_lyric_function)
	{
		backend.SendLyric(context->ContextRecord->Eax);

		//恢复程序的正常运行
		context->ContextRecord->Eip = (DWORD)&ToUpdateLyricFunction;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else if (context->ExceptionRecord->ExceptionAddress == (PVOID)backend.update_translation_function)
	{
		backend.SendTranslation(context->ContextRecord->Eax);

		context->ContextRecord->Eip = (DWORD)&ToUpdateTranslationFunction;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

void StartWatching()
{
	CONTEXT context = {};
	context.ContextFlags = 65599;

	GetThreadContext(GetCurrentThread(), &context);

	context.Dr0 = backend.update_lyric_function;
	context.Dr1 = backend.update_translation_function;
	context.Dr7 = 1109;

	context.ContextFlags = 65599;
	SetThreadContext(GetCurrentThread(), &context);

}
