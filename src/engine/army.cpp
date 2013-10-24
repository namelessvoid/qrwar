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
		if(units.add(unit))
		{
			undeployedunits.add(unit);
			return true;
		}
		return false;
	}

	void Army::deleteAllUnits()
	{
		units.deleteUnits();
		undeployedunits.clear();
		deployedunits.clear();
	}

	std::set<Unit*>& Army::getUnitsByType(UNITTYPES unittype)
	{
		return (std::set<Unit*>&) units.getUnitsByType(unittype);
	}

	int* Army::getTotalUnitCount()
	{
		return units.getTotalUnitCount();
	}

	int Army::getUnitCount(UNITTYPES unittype)
	{
		return units.getUnitCount(unittype);
	}

	std::set<Unit*>& Army::getUndeployedUnitsByType(UNITTYPES unittype)
	{
		return (std::set<Unit*>&) undeployedunits.getUnitsByType(unittype);
	}

	bool Army::markUnitAsDeployed(Unit* unit)
	{
		if(undeployedunits.contains(unit))
		{
			deployedunits.add(unit);
			undeployedunits.remove(unit);
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