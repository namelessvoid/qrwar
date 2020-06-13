#include "game/skirmish/unitability.hpp"

#include "game/skirmish/unit.hpp"

namespace qrw
{

UnitAbility::UnitAbility(Unit* owner)
	: GameComponent(*owner),
	  unit_(owner),
	  isActive_(false),
	  enabled_(true)
{}

}
