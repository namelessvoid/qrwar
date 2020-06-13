#ifndef QRW_UNITABILITY_HPP
#define QRW_UNITABILITY_HPP

#include "foundation/gamecomponent.hpp"

#include "eventsystem/eventhandler.hpp"
#include "eventsystem/eventsystem.hpp"

#include "game/eventhandlerpriority.hpp"

namespace qrw
{
class Unit;

class UnitAbility : public GameComponent
{
public:
	explicit UnitAbility(Unit* owner);

	~UnitAbility() override = default;

	virtual void activate()	{ isActive_ = true; }

	virtual void deactivate() { isActive_ = false; }

	virtual void executeOn(const Coordinates& position) = 0;

	virtual bool canBeExecutedOn(const Coordinates& position) { return enabled_; };

	virtual void updateActiveVisualization(const Coordinates& position) = 0;

	inline const std::string& getName() { return name_; }

	bool isEnabled() const { return enabled_; }
	void setEnabled(bool enabled) { enabled_ = enabled; }

protected:
	inline void setName(const std::string& name) { name_ = name; }

	Unit* unit_;

private:
	bool isActive_;

	bool enabled_;

	std::string name_;
};

} // namespace qrw

#endif //QRW_UNITABILITY_HPP
