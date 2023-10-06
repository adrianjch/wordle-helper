#pragma once
#include <string>

inline std::string ReplaceString(const std::string& original, const std::string& from, const std::string& to)
{
	auto x = original.find(from);
	if (x == std::string::npos)
	{
		return original;
	}

	auto ret = original;
	ret.replace(x, from.length(), to);
	return ret;
}
