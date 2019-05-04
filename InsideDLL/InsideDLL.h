#pragma once
#include <string>

//负责与前端进程进行通信
class Backend
{
public:

	//baseptr = 83 7C 24 40 08 8D 44 24 2C 8B 4E 30 0F 43 44 24 2C 50 E8 ?? ?? ?? ?? 83 7C 24 28 08 8D 44 24 14 8B 4E 34 0F 43 44 24 14

	/*!更新歌词函数入口，调用时eax为指向歌词字符串的指针*/
	DWORD update_lyric_function = 0x63716E90;  // baseptr + 17 //6801FE2B    50              push eax
	/*!更新翻译过的歌词的函数入口，调用时eax为指向翻译*/
	DWORD update_translation_function = 0x63718D60;// baseptr + 40 // 6801FE42    50              push eax

	/*!
	向前端发送捕获的歌词数据，歌词数据为Unicode字符串
	参数：unicodePTR | 指向歌词字符串的指针
	返回：无
	*/
	void SendLyric(DWORD unicodePTR);

	/*!
	向前端发送捕获的经过翻译的歌词数据，歌词数据为Unicode字符串
	参数：unicodePTR | 指向歌词字符串的指针
	返回：无
	*/
	void SendTranslation(DWORD unicodePTR);
private:
	void SendData(std::wstring &data);
};

//VEH处理
LONG Handler(PEXCEPTION_POINTERS context);

//HOOK歌词更替函数
void StartWatching();