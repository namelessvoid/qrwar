#ifndef QRW_DEPLOYLADDERABILITY_HPP
#define QRW_DEPLOYLADDERABILITY_HPP

#include "unitspecialability.hpp"

#include "gui/scene.hpp"

#include "game/skirmish/ladder.hpp"
#include "game/skirmish/wall.hpp"

namespace qrw
{

class DeployLadderAbility : public UnitSpecialAbility
{
public:
	DeployLadderAbility(Unit* owner)
		: UnitSpecialAbility(owner)
	{
		setName("Deploy Ladder");
	}

	void executeOn(const Coordinates& position) override
	{
		Board* board = g_scene.findSingleGameObject<Board>();
		if(!board) return;

		Ladder* ladder = g_scene.spawn<Ladder>();
		ladder->setPosition(owner_->getPosition());
		ladder->setFace(position - ladder->getPosition());
		board->setStructure(ladder->getPosition(), ladder);
	}

	bool canBeExecutedOn(const Coordinates& position) override
	{
		Board* board = g_scene.findSingleGameObject<Board>();
		if(!board) return false;

		return owner_->getPosition().distanceTo(position) == 1
			&& board->getStructure(owner_->getPosition()) == nullptr
			&& dynamic_cast<Wall*>(board->getStructure(position)) != nullptr;
	}
};

} // namespace qrw

#endif //QRW_DEPLOYLADDERABILITY_HPP
