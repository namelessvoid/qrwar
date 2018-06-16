#ifndef QRW_REFLECTABLE_HPP
#define QRW_REFLECTABLE_HPP

namespace qrw {

class Reflectable
{
public:
	Reflectable(const Reflectable& rhs) = delete;

	Reflectable& operator=(const Reflectable& rhs) = delete;

	Reflectable() = default;

	virtual ~Reflectable() = default;
};


} // namespace qrw

#endif // QRW_REFLECTABLE_HPP
