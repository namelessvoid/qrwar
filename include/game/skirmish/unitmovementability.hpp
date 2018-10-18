#ifndef QRW_UNITMOVEMENTABILITY_HPP
#define QRW_UNITMOVEMENTABILITY_HPP

#include "unitspecialability.hpp"

namespace qrw
{

class UnitMovementAbility : public UnitSpecialAbility
{
public:
	void deactivate() override;

	explicit UnitMovementAbility(Unit* owner);

	void onDestroy() override;

	UnitMovementAbility(const UnitMovementAbility& rhs) = delete;
	UnitMovementAbility& operator=(const UnitMovementAbility& rhs) = delete;

	void executeOn(const Coordinates& position) override;

	bool canBeExecutedOn(const Coordinates& position) override;

	void updateVisualization(const Coordinates& position) override;

private:
	class Path* path_;
};

} // namespace qrw

#endif //QRW_UNITMOVEMENTABILITY_HPP
