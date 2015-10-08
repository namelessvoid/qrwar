#ifndef QRW_UNITENTITY_H
#define QRW_UNITENTITY_H

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/unit.hpp"

namespace qrw
{

class UnitEntity : public sf::RectangleShape
{
public:
	typedef std::shared_ptr<Unit> Ptr;

	Ptr createUnitEntity(Unit::Ptr unit, int dimension);

private:
	UnitEntity();
};

} // namespace qrw

#endif // QRW_UNITENTITY_H
