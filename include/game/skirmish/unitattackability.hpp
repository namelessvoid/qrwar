#ifndef QRW_UNITATTACKABILITY_HPP
#define QRW_UNITATTACKABILITY_HPP

#include "unitability.hpp"

namespace qrw
{

class UnitAttackAbility : public UnitAbility
{
public:
	explicit UnitAttackAbility(Unit* owner);

	UnitAttackAbility(const UnitAttackAbility& rhs) = delete;
	UnitAttackAbility& operator=(const UnitAttackAbility& rhs) = delete;

	void updateVisualization(const Coordinates& position) override
	{}

	void executeOn(const Coordinates& position) override;

	bool canBeExecutedOn(const Coordinates& position) override;

protected:
	void counterAttack(Unit& opponent);

private:
	void inflictDamage(Unit& opponent);

	Unit* getOpponentAt(const Coordinates& position);
};

} // namespace qrw

#endif //QRW_UNITATTACKABILITY_HPP
