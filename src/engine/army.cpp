#include "engine/army.hpp"

namespace qrw
{
	Army::Army()
	{
	}

	Army::~Army()
	{
	}

	bool Army::addUnit(Unit* unit)
	{
		// Unit already added?
		return units.add(unit);
	}

	void Army::clear()
	{
		units.clear();
		deployedunits.clear();
	}

	int* Army::getTotalUnitCount()
	{
		return units.getTotalUnitCount();
	}

	int Army::getUnitCount(UNITTYPES unittype)
	{
		return units.getUnitCount(unittype);
	}

	bool Army::deployUnit(Unit* unit)
	{
		if(units.contains(unit) && !deployedunits.contains(unit))
		{
			deployedunits.add(unit);
			return true;
		}
		return false;
	}

	int* Army::getTotalDeployedUnitCount()
	{
		return deployedunits.getTotalUnitCount();
	}

	int Army::getDeployedUnitCount(UNITTYPES unittype)
	{
		return deployedunits.getUnitCount(unittype);
	}
}