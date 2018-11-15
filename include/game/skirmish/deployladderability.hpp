#ifndef QRW_DEPLOYLADDERABILITY_HPP
#define QRW_DEPLOYLADDERABILITY_HPP

#include <memory>

#include "unitability.hpp"

#include "foundation/spritecomponent.hpp"

namespace qrw
{
class Unit;
class Coordinates;

class DeployLadderAbility : public UnitAbility
{
public:
	explicit DeployLadderAbility(Unit* owner);

	void activate() override;
	void deactivate() override;
	void updateActiveVisualization(const Coordinates& position) override;

	void executeOn(const Coordinates& position) override;

	bool canBeExecutedOn(const Coordinates& position) override;

protected:
	std::unique_ptr<SpriteComponent> deploySymbol_;
};

class LadderDeployedEvent : public EventBase<LadderDeployedEvent>
{
};

} // namespace qrw

#endif //QRW_DEPLOYLADDERABILITY_HPP
