#include "stdafx.h"
#include "sunday.h"

unsigned long long SundaySearch::search(const std::vector<char> &srcArray, const std::vector<char> &subArray)
{
	
	const size_t srclen = srcArray.size();
	const size_t sublen = subArray.size();

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
			for (size_t j = 0; j < sublen; ++j)
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