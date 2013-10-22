#include "engine/army.hpp"

namespace qrw
{
	Army::Army()
	{
	}

	Army::~Army()
	{
	}

	void Army::addUnit(Unit* unit)
	{
		// Unit already added?
		for(auto iter = units.begin(); iter != units.end(); ++iter)
			if((*iter) == unit)
				return;

		units.push_back(unit);
	}

	std::vector<Unit*>& Army::getUnits()
	{
		return units;
	}

	int* Army::getUnitCount()
	{
		return NULL;
	}

	void Army::deployUnit(Unit* unit)
	{
		// Was the unit already added to the army?
		bool added = false;
		for(auto iter = units.begin(); iter != units.end(); ++iter)
		{
			if((*iter) == unit)
			{
				added = true;
				break;
			}
		}
		if(added)
			deployedunits.push_back(unit);
	}

	int* Army::getDeployedUnitCount()
	{
		return NULL;
	}

	std::vector<Unit*>& Army::getDeployedUnits()
	{
		return deployedunits;
	}
}