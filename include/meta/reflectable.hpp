#ifndef QRW_REFLECTABLE_HPP
#define QRW_REFLECTABLE_HPP

#include "core/sid.hpp"

namespace qrw {

class Reflectable
{
public:
	Reflectable() = default;

	virtual ~Reflectable() = default;

	virtual const SID& getTypeName() const = 0;
};


} // namespace qrw

#endif // QRW_REFLECTABLE_HPP
