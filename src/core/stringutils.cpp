#include "core/stringutils.hpp"

#include <algorithm>

namespace qrw
{

void replaceAll(std::string& str, const std::string& find, const std::string& replace)
{
	if(str.empty() || find.empty() || replace.empty())
		return;

	size_t startPos = 0;
	while((startPos = str.find(find, startPos)) != std::string::npos)
	{
		str.replace(startPos, find.length(), replace);
		startPos += replace.length();
	}
}

void toLower(std::string& string)
{
	std::transform(string.begin(), string.end(), string.begin(), ::tolower);
}

} // namespace qrw
