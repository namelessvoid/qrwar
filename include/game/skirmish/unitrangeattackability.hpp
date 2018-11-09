#ifndef QRW_UNITRANGEATTACKABILITY_HPP
#define QRW_UNITRANGEATTACKABILITY_HPP

#include "unitability.hpp"

#include "gui/squaremarker.hpp"

namespace qrw
{

class UnitRangeAttackAbility : public UnitAbility
{
public:
	explicit UnitRangeAttackAbility(Unit* owner);

	void executeOn(const Coordinates& position) override;

	bool canBeExecutedOn(const Coordinates& position) override;

	void activate() override;
	void deactivate() override;

	void updateActiveVisualization(const Coordinates& position) override;

private:
	unsigned int minRange_;
	unsigned int maxRange_;
	unsigned int damage_;

	SquareMarker* squareMarker_;
};

} // namespace qrw


#endif //QRW_UNITRANGEATTACKABILITY_HPP
