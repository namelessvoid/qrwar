#ifndef QRW_STRINGUTILS_HPP
#define QRW_STRINGUTILS_HPP

#include <string>

namespace qrw
{

void replaceAll(std::string& str, const std::string& find, const std::string& replace);

void toLower(std::string& str);

} // namespace qrw

#endif // QRW_STRINGUTILS_HPP
