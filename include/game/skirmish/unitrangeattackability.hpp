#ifndef QRW_UNITRANGEATTACKABILITY_HPP
#define QRW_UNITRANGEATTACKABILITY_HPP

#include "unitability.hpp"

namespace qrw
{

class UnitRangeAttackAbility : public UnitAbility
{
public:
	explicit UnitRangeAttackAbility(Unit* owner);

	void executeOn(const Coordinates& position) override;

	bool canBeExecutedOn(const Coordinates& position) override;

	void updateActiveVisualization(const Coordinates& position) override;

private:
	unsigned int minRange_;
	unsigned int maxRange_;
	unsigned int damage_;
};

} // namespace qrw


#endif //QRW_UNITRANGEATTACKABILITY_HPP
