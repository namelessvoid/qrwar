#ifndef QRW_UNITFACTORY_HPP
#define QRW_UNITFACTORY_HPP

#include "unit.hpp"
#include "unittypes.hpp"

namespace qrw
{

class UnitFactory
{
public:
	static Unit* createUnit(UNITTYPES unitType, Player::Ptr player);
};

} // namespace qrw

#endif //QRW_UNITFACTORY_HPP
