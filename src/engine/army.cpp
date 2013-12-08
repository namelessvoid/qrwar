#include "engine/army.hpp"

namespace qrw
{
	Army::Army()
		:	maxsize(0)
	{
	}

	Army::~Army()
	{
	}

	void Army::setMaxSize(int maxsize)
	{
		this->maxsize = maxsize;
	}

	bool Army::isFull()
	{
		int* unittypecount = getUnitCount();
		int totalcount = 0;
		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
		{
			totalcount += unittypecount[i];
		}
		return totalcount >= maxsize;
	}

	bool Army::addUnit(Unit* unit)
	{
		if(isFull())
			return false;

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

	int* Army::getUnitCount()
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