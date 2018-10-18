#ifndef QRW_UNITSPECIALABILITY_HPP
#define QRW_UNITSPECIALABILITY_HPP

#include "foundation/gamecomponent.hpp"

#include "eventsystem/eventhandler.hpp"
#include "eventsystem/eventsystem.hpp"

#include "game/eventhandlerpriority.hpp"

namespace qrw
{
class Unit;

class UnitSpecialAbility : public GameComponent
{
public:
	explicit UnitSpecialAbility(Unit* owner)
		: owner_(owner),
		  isActive_(false)
	{
	}

	~UnitSpecialAbility() override = default;

	void activate()
	{
		std::cout << "Special ability '" << getName() << "' is activated\n" << std::flush;
		isActive_ = true;
	}

	virtual void deactivate()
	{
		std::cout << "Ability '" << getName() << "' is deactivated\n" << std::flush;
		isActive_ = false;
	}

	virtual void executeOn(const Coordinates& position) = 0;

	virtual bool canBeExecutedOn(const Coordinates& position) = 0;

	virtual void updateVisualization(const Coordinates& position) = 0;

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
