#ifndef QRW_STAIRS_HPP
#define QRW_STAIRS_HPP

#include "imakewallaccessible.hpp"

namespace qrw
{

class Stairs : public IMakeWallAccessible
{
public:
	friend class StairsMetaClass;

	static SID typeName;
	const SID& getTypeName() const override	{ return typeName; }

	Stairs();
};

} // namespace qrw

#endif //QRW_STAIRS_HPP
