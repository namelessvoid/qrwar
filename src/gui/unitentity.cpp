#include "gui/unitentity.hpp"

#include "engine/unit.hpp"
#include "engine/coordinates.hpp"
#include "engine/player.hpp"

#include "gui/texturemanager.hpp"
#include "gui/guihelper.hpp"

namespace qrw {

UnitEntity::Ptr UnitEntity::createUnitEntity(Unit::Ptr unit, int dimension)
{
	return Ptr(new UnitEntity(unit, dimension));
}

const Coordinates& UnitEntity::getBoardPosition() const
{
	return _unit->getPosition();
}

UnitEntity::UnitEntity(Unit::Ptr unit, int dimension)
	: _unit(unit)
{
	setSize(sf::Vector2f(dimension, dimension));

	const Coordinates boardPosition = _unit->getPosition();
	setPosition(sf::Vector2f(dimension * boardPosition.getX(), dimension * boardPosition.getY()));

    setTexture(GuiHelper::getUnitTexture(unit));
}

} // namespace qrw
