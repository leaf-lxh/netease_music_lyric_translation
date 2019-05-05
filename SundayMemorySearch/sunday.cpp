#include "stdafx.h"
#include "sunday.h"

#include <sstream>

unsigned int SundaySearch::Search(const std::vector<char> &srcArray, const std::vector<char> &subArray)
{
	
	const size_t srclen = srcArray.size();
	const size_t sublen = subArray.size();

	if (srclen < sublen)
	{
		return UINT_MAX;
	}

	size_t matchedLen = 0;

	for (size_t i = 0; i < srclen;)
	{
		if (subArray[matchedLen] == srcArray[i])
		{
			++matchedLen;
			++i;
			if (matchedLen == sublen)
			{
				return i - matchedLen;
			}
		}
		else
		{
			size_t index = i - matchedLen + sublen;
			i = index;
			matchedLen = 0;

			if (index >= srclen)
			{
				return UINT_MAX;
			}
			for (size_t j = sublen - 1; j >= 0; --j)
			{
				if (subArray[j] == srcArray[index])
				{
					i = index - j;
					break;
				}
			}
		}
	}

	return UINT_MAX;
}



unsigned int SundaySearch::FuzzSearch(const std::vector<char> &srcArray, const std::string &pattern)
{
	std::vector<bool> fuzzPosition = this->FindFuzzPos(pattern);
	return UINT_MAX;
}

std::vector<bool> SundaySearch::FindFuzzPos(const std::string & pattern)
{
	
	return std::vector<bool>();
}

std::vector<char> SundaySearch::PatternToArray(const std::string & pattern)
{
	return std::vector<char>();
}
