#pragma once

#include "sunday.h"
#include <Windows.h>

#include <vector>

/*!
�ṩ�������ڴ�ķ�����ʹ��Sunday�ַ���ƥ���㷨
ͬʱҲ�ṩ��ͨ�������������������ƣ����λ�û�ȡ����ID�ķ���
32λ��64λϵͳ��֧�֣�����64λ֧����Ҫ��x64��ʽ����
������MemorySearchx64
���ࣺSundaySearch
*/
class MemorySearchx64 : public SundaySearch
{
public:
	/*!
	���ݴ�������ȡ�����ô��ڵĽ��̵Ľ��̱�ʶ��
	������windowName      | ���ڱ��⣬�粻��Ҫ�жϣ����ݿ��ַ���
	������windowClassName | �����������粻��Ҫ�жϣ����ݿ��ַ���
	���أ����̱�ʶ��������ʧ��vector.size=0
	*/
	std::vector<DWORD_PTR> GetPidByWindow(std::string windowName, std::string windowClassName);

	/*!
	���ݽ��̽������Ʒ��ؽ��̱�ʶ��
	������processName | ����������ܿ����Ľ������ƣ���abc.exe
	���أ����̱�ʶ��������ʧ��vector.size=0
	*/
	std::vector<DWORD_PTR> GetPidByProcessName(std::string processName);

	/*!
	��ȡ���λ���µĴ���
	������pos | ���ָ�������
	���أ����̱�ʶ��������ʧ�ܷ���NULL
	*/
	DWORD_PTR GetPidByCursorPos(POINT pos);

	/*!
	����pattern�����ڴ棬���ط�����������ʼ�ڴ��ַ
	������startAddress | ��������ʼ�ڴ��ַ
	������stopAddress  | ��������ֹ�ڴ��ַ
	������pattern      | ������������
	���أ������������ڴ��ַ����ѯʧ��vector.size=0
	*/
	std::vector<DWORD_PTR> SearchArray(DWORD_PTR startAddress, DWORD_PTR stopAddress, std::vector<char> pattern);
};