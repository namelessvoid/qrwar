#ifndef QRW_UNITMEELEATTACKABILITY_HPP
#define QRW_UNITMEELEATTACKABILITY_HPP

#include <memory>

#include "unitability.hpp"

#include "foundation/spritecomponent.hpp"

namespace qrw
{

class UnitMeleeAttackAbility : public UnitAbility
{
public:
	explicit UnitMeleeAttackAbility(Unit* owner);

	void activate() override;
	void deactivate() override;

	void updateActiveVisualization(const Coordinates& position) override;

	void executeOn(const Coordinates& position) override;

	bool canBeExecutedOn(const Coordinates& position) override;

	UnitMeleeAttackAbility(const UnitMeleeAttackAbility& rhs) = delete;
	UnitMeleeAttackAbility& operator=(const UnitMeleeAttackAbility& rhs) = delete;

protected:
	void counterAttack(Unit& opponent);

private:
	void inflictDamage(Unit& opponent);
	inline unsigned int getAttackRange() { return 1; }

	Unit* getOpponentAt(const Coordinates& position);

	std::unique_ptr<SpriteComponent> attackSymbol_;
};

} // namespace qrw

#endif //QRW_UNITMEELEATTACKABILITY_HPP
