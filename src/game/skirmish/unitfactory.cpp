#include "game/skirmish/unitfactory.hpp"

#include "gui/guihelper.hpp"
#include "gui/scene.hpp"

#include "game/skirmish/laddercarrier.hpp"

namespace qrw
{

Unit* UnitFactory::createUnit(UNITTYPES unitType, Player::Ptr player)
{
	if(unitType == EUT_LADDERCARRIER)
	{
		Unit* unit = new LadderCarrier();
		unit->setPlayer(player);
		return unit;
	}

	const sf::Texture* texture = GuiHelper::getUnitTexture(unitType, player->getId());

	int maxHp = 0;
	int attack = 0;
	int defense = 0;
	int range = 0;
	int movement = 0;

	switch(unitType)
	{
		case EUT_SWORDMAN:
			maxHp    = 5;
			attack   = 2;
			defense  = 1;
			range    = 1;
			movement = 3;
			break;
		case EUT_ARCHER:
			maxHp    = 5;
			attack   = 2;
			defense  = 1;
			range    = 2;
			movement = 2;
			break;
		case EUT_SPEARMAN:
			maxHp    = 5;
			attack   = 2;
			defense  = 1;
			range    = 1;
			movement = 2;
			break;
		default:
			assert(false);
	}

	Unit* unit = g_scene.spawn<Unit>();
	unit->setType(unitType);
	unit->setMaxHp(maxHp);
	unit->setCurrentHp(maxHp);
	unit->setAttack(attack);
	unit->setDefense(defense);
	unit->setRange(range);
	unit->setMaxMovement(movement);
	unit->setCurrentMovement(movement);
	unit->setPlayer(player);
	unit->setTexture(texture);
	return unit;
}

} // namespace qrw