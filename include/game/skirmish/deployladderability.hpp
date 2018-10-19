#ifndef QRW_DEPLOYLADDERABILITY_HPP
#define QRW_DEPLOYLADDERABILITY_HPP

#include "unitspecialability.hpp"

namespace qrw
{
class Unit;
class Coordinates;

class DeployLadderAbility : public UnitSpecialAbility
{
public:
	explicit DeployLadderAbility(Unit* owner);

	void executeOn(const Coordinates& position) override;

	bool canBeExecutedOn(const Coordinates& position) override;

	void updateVisualization(const Coordinates& position) override {}
};

class LadderDeployedEvent : public EventBase<LadderDeployedEvent>
{
};

} // namespace qrw

#endif //QRW_DEPLOYLADDERABILITY_HPP
