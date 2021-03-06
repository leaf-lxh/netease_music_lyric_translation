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
	std::vector<char> subArray = this->PatternToArray(pattern);


	const size_t srclen = srcArray.size();
	const size_t sublen = subArray.size();

	if (srclen < sublen)
	{
		return UINT_MAX;
	}

	size_t matchedLen = 0;

	for (size_t i = 0; i < srclen;)
	{
		if (fuzzPosition[matchedLen] == true || subArray[matchedLen] == srcArray[i])
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
				if (fuzzPosition[j] == true || subArray[j] == srcArray[index])//bug
				{
					i = index - j;
					break;
				}
			}
		}
	}

	return UINT_MAX;
}

std::vector<bool> SundaySearch::FindFuzzPos(const std::string & pattern)
{
	size_t patternLen = pattern.length();
	std::vector<bool> result;
	
	for (size_t pos = 0; pos < patternLen; ++pos)
	{
		if (pattern[pos] == ' ')
		{
			if (pattern.substr(pos - 2, pos).compare("??") == 0)
			{
				result.push_back(true);
			}
			else
			{
				result.push_back(false);
			}
		}
	}

	return result;
}

std::vector<char> SundaySearch::PatternToArray(const std::string & pattern)
{
	size_t patternLen = pattern.length();
	std::vector<char> result;

	std::stringstream stream;
	for (size_t pos = 0; pos < patternLen; ++pos)
	{
		if (pattern[pos] == ' ')
		{
			std::string strbyte = pattern.substr(pos - 2, pos);
			int charbyte = 0;
			if (strbyte.compare("??") == 0)
			{
				result.push_back(0);
			}
			else
			{
				stream << std::hex << strbyte;
				stream >> charbyte;
				stream.str("");
				stream.clear();

				result.push_back(charbyte);
			}
		}
	}

	return result;
}
