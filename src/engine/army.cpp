#include "engine/army.hpp"

namespace qrw
{
	Army::Army()
		:	_maxsize(0)
	{
	}

	Army::~Army()
	{
	}

	void Army::setMaxSize(int maxsize)
	{
		this->_maxsize = maxsize;
	}

	bool Army::isFull()
	{
		return getTotalUnitCount() >= _maxsize;
	}

	bool Army::addUnit(Unit* unit)
	{
		if(isFull())
			return false;

		if(_units.add(unit))
		{
			_undeployedunits.add(unit);
			return true;
		}
		return false;
	}

	void Army::deleteAllUnits()
	{
		_units.deleteUnits();
		_undeployedunits.clear();
		_deployedunits.clear();
	}

	std::set<Unit*>& Army::getUnitsByType(UNITTYPES unittype)
	{
		return (std::set<Unit*>&) _units.getUnitsByType(unittype);
	}

	int* Army::getUnitCount()
	{
		return _units.getTotalUnitCount();
	}

	int Army::getUnitCount(UNITTYPES unittype)
	{
		return _units.getUnitCount(unittype);
	}

	int Army::getTotalUnitCount()
	{
		int* unitcount = getUnitCount();
		int totalcount = 0;
		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
			totalcount += unitcount[i];
		return totalcount;
	}
	std::set<Unit*>& Army::getUndeployedUnitsByType(UNITTYPES unittype)
	{
		return (std::set<Unit*>&) _undeployedunits.getUnitsByType(unittype);
	}

	bool Army::markUnitAsDeployed(Unit* unit)
	{
		if(_undeployedunits.contains(unit))
		{
			_deployedunits.add(unit);
			_undeployedunits.remove(unit);
			return true;
		}
		return false;
	}

	int* Army::getTotalDeployedUnitCount()
	{
		return _deployedunits.getTotalUnitCount();
	}

	int Army::getDeployedUnitCount(UNITTYPES unittype)
	{
		return _deployedunits.getUnitCount(unittype);
	}
}
