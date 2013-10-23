#include "engine/unitsmap.hpp"

namespace qrw
{
	UnitsMap::UnitsMap()
	{
		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
			units[(UNITTYPES)i] = new std::set<Unit*>();
	}

	UnitsMap::~UnitsMap()
	{
		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
			delete units[(UNITTYPES)i];
	}

	bool UnitsMap::add(Unit* unit)
	{
		if(!contains(unit))
		{
			units[unit->getType()]->insert(unit);
			return true;
		}
		return false;
	}

	bool UnitsMap::remove(Unit* unit)
	{
		if(units[unit->getType()]->erase(unit) >= 1)
			return true;
		return false;
	}

	void UnitsMap::deleteUnits()
	{
		std::set<Unit*>* unitset;
		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
		{
			unitset = units[(UNITTYPES)i];

			for(auto iter = unitset->begin(); iter != unitset->end(); ++iter)
				delete *iter;

			unitset->clear();
		}
	}

	bool UnitsMap::contains(Unit *unit)
	{
		// explanation: find(unit) != set::end
		return units[unit->getType()]->find(unit) != units[unit->getType()]->end();
	}

	int* UnitsMap::getTotalUnitCount()
	{
		int* unitcounts = new int[EUT_NUMBEROFUNITTYPES];

		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
			unitcounts[i] = getUnitCount((UNITTYPES)i);

		return unitcounts;
	}

	int UnitsMap::getUnitCount(UNITTYPES unittype)
	{
		return units[unittype]->size();
	}

	const std::set<Unit*>& UnitsMap::getUnitsByType(UNITTYPES unittype)
	{
		return *units[unittype];
	}
}