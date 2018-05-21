#ifndef QRW_REFLECTABLE_HPP
#define QRW_REFLECTABLE_HPP

namespace qrw {

class Reflectable
{
protected:
	Reflectable() {}

	virtual ~Reflectable() {}

private:
	Reflectable(const Reflectable& rhs) = delete;

	Reflectable& operator=(const Reflectable& rhs) = delete;
};


} // namespace qrw

#endif // QRW_REFLECTABLE_HPP
