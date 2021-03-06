#pragma once

#include <vector>


class SundaySearch
{
public:

	SundaySearch() = default;

	/*!
	搜索子串在源字符串中第一次出现的位置
	参数：srcArray | 被搜索的源字符串
	参数：subArray | 搜索用的字串
	返回：第一次出现的位置，索引从0开始，找不到返回UINIT_MAX
	*/
	unsigned int Search(const std::vector<char> &srcArray, const std::vector<char> &subArray);

	/*!
	模糊搜索子串在源字符串中第一次出现的位置
	参数：srcArray | 源字符串
	参数：pattern  | 模式串，每一个字节后面需要加一个空格，每一个字节应以十六进制数值表示。比如0A 2B 3C ?? 5F FF ?? 00 
	返回：第一次出现的位置，索引从0开始，找不到返回UINIT_MAX
	*/
	unsigned int FuzzSearch(const std::vector<char> &srcArray, const std::string &pattern);

	~SundaySearch() = default;

private:
	/*!
	扫描模式串，生成一个记录了模糊元素的位置的表
	参数：pattern | 模式串
	返回：记录模糊元素的位置的表
	*/
	std::vector<bool> FindFuzzPos(const std::string &pattern);

	/*!
	将模式串转换成字节序列
	参数：pattern | 模式串
	返回：字节序列
	*/
	std::vector<char> PatternToArray(const std::string &pattern);
};

