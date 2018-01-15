#ifndef QRW_SID_HPP
#define QRW_SID_HPP

#include <functional>
#include <iostream>

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

	SID(const SID& rhs)
		: m_stringId(rhs.m_stringId),
		  m_hashId(rhs.m_hashId)
	{
	}

    bool operator==(const SID& rhs) const
    {
        return m_hashId == rhs.m_hashId;
    }

	bool operator<(const SID& rhs) const
	{
		return m_hashId < rhs.m_hashId;
	}

	const std::string& getStringId()
	{
		return m_stringId;
	}

	friend std::ostream& operator<<(std::ostream& os, const SID& sid)
	{
		os << sid.m_stringId;
		return os;
	}

private:
    const std::string m_stringId;
    const std::size_t m_hashId;
};

} // namespace qrw

#endif // QRW_SID_HPP
