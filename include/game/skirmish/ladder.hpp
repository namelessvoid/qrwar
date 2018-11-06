#ifndef QRW_LADDER_HPP
#define QRW_LADDER_HPP

#include "stairs.hpp"

namespace qrw
{

class Ladder : public WallAccessStructureBase
{
public:
	const SID& getTypeName() const override;

	Ladder();
};

} // namespace qrw

#endif // QRW_LADDER_HPP
