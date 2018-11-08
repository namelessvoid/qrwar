#ifndef QRW_UNITMEELEATTACKABILITY_HPP
#define QRW_UNITMEELEATTACKABILITY_HPP

#include "unitability.hpp"

namespace qrw
{

class UnitMeleeAttackAbility : public UnitAbility
{
public:
	explicit UnitMeleeAttackAbility(Unit* owner);

	UnitMeleeAttackAbility(const UnitMeleeAttackAbility& rhs) = delete;
	UnitMeleeAttackAbility& operator=(const UnitMeleeAttackAbility& rhs) = delete;

	void updateActiveVisualization(const Coordinates& position) override
	{}

	void executeOn(const Coordinates& position) override;

	bool canBeExecutedOn(const Coordinates& position) override;

protected:
	void counterAttack(Unit& opponent);

private:
	void inflictDamage(Unit& opponent);
	inline unsigned int getAttackRange() { return 1; }

	Unit* getOpponentAt(const Coordinates& position);
};

} // namespace qrw

#endif //QRW_UNITMEELEATTACKABILITY_HPP
