#pragma once
#include <string>

//������ǰ�˽��̽���ͨ��
class Backend
{
public:

	//baseptr = 83 7C 24 40 08 8D 44 24 2C 8B 4E 30 0F 43 44 24 2C 50 E8 ?? ?? ?? ?? 83 7C 24 28 08 8D 44 24 14 8B 4E 34 0F 43 44 24 14

	/*!���¸�ʺ�����ڣ�����ʱeaxΪָ�����ַ�����ָ��*/
	DWORD update_lyric_function = 0x63716E90;  // baseptr + 17 //6801FE2B    50              push eax
	/*!���·�����ĸ�ʵĺ�����ڣ�����ʱeaxΪָ����*/
	DWORD update_translation_function = 0x63718D60;// baseptr + 40 // 6801FE42    50              push eax

	/*!
	��ǰ�˷��Ͳ���ĸ�����ݣ��������ΪUnicode�ַ���
	������unicodePTR | ָ�����ַ�����ָ��
	���أ���
	*/
	void SendLyric(DWORD unicodePTR);

	/*!
	��ǰ�˷��Ͳ���ľ�������ĸ�����ݣ��������ΪUnicode�ַ���
	������unicodePTR | ָ�����ַ�����ָ��
	���أ���
	*/
	void SendTranslation(DWORD unicodePTR);
private:
	void SendData(std::wstring &data);
};

//VEH����
LONG Handler(PEXCEPTION_POINTERS context);

//HOOK��ʸ��溯��
void StartWatching();