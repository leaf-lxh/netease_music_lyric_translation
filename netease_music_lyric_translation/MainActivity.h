#pragma once
#include <Windows.h>

class Front
{
public:
	DWORD StartListen();
	DWORD StopListen();

private:
	void UpdateLyric(LPCTSTR lyric);
	void UpdateTranslation(LPCTSTR translation);
};