#pragma once

#include <vector>


class SundaySearch
{
public:

	SundaySearch() = default;

	unsigned long long search(const std::vector<char> &srcArray, const std::vector<char> &subArray);

	~SundaySearch() = default;
};

