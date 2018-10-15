#ifndef QRW_UNITSPECIALABILITY_HPP
#define QRW_UNITSPECIALABILITY_HPP

#include "eventsystem/eventhandler.hpp"
#include "eventsystem/eventsystem.hpp"

#include "game/eventhandlerpriority.hpp"

namespace qrw
{
class Unit;

class UnitSpecialAbility
{
public:
	explicit UnitSpecialAbility(Unit* owner)
		: owner_(owner),
		  isActive_(false)
	{
	}

	virtual ~UnitSpecialAbility() = default;

	void activate()
	{
		isActive_ = true;
	}

	void deactivate()
	{
		isActive_ = false;
	}

	virtual void executeOn(const Coordinates& position) = 0;

	virtual bool canBeExecutedOn(const Coordinates& position) = 0;

	inline const std::string& getName() { return name_; }

protected:
	inline void setName(const std::string& name) { name_ = name; }

	Unit* owner_;

private:
	bool isActive_;

	std::string name_;
};

} // namespace qrw

#endif //QRW_UNITSPECIALABILITY_HPP
