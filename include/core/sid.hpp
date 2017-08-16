#ifndef QRW_SID_HPP
#define QRW_SID_HPP

#include <functional>

namespace qrw
{

class SID
{
public:
    SID(const std::string& identifier)
        : m_stringId(identifier),
          m_hashId(std::hash<std::string>{}(identifier))
    {
    }

    SID(const SID& rhs) = delete;

    bool operator==(const SID& rhs) const
    {
        return m_hashId == rhs.m_hashId;
    }

private:
    const std::string m_stringId;
    const std::size_t m_hashId;
};

} // namespace qrw

#endif // QRW_SID_HPP
