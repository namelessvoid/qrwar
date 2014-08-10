#ifndef QRW_UNITSSLIST_HPP
#define QRW_UNITSLIST_HPP

#include <set>
#include <map>

#include "engine/unittypes.hpp"

namespace qrw
{
	class Unit;

	/**
	 * @brief Used to save units ordered by UNITTYPES.
	 *
	 * The UnitsMap is a wrapper class for a std::map containing std::sets of unit pointers. It's a more convenient way
	 * of managing a bunch of units.
	 */
	class UnitsMap
	{
		public:
			/**
			 * Standard ctor.
			 */
			UnitsMap();

			/**
			 * Standard dtor.
			 */
			~UnitsMap();

			bool add(Unit* unit);
			bool remove(Unit* unit);
			void deleteUnits();
			void clear();
			bool contains(Unit* unit);

			/**
			 * @brief Get the number of units separated by UNITTYPES.
			 *
			 * Get the number of units that have been added (addUnit()).
			 * @return Integer array which holds the unit count for each UNITTYPES and has size UNITTYPES::EUT_NUMBEROFUNITTYPES.
			 * @see UNITTYPES
			 */
			int* getTotalUnitCount();

			/**
			 * @brief Get the number of units of given unittype.
			 *
			 * @paran unittype The type of the unit.
			 * @return The number of units of type unittype as integer.
			 */
			int getUnitCount(UNITTYPES unittype);

			/**
			 * @brief Get units by unittype.
			 *
			 * Get a set of units of unittype that have been added via addUnit().
			 * @paran unittype The type of the units.
			 * @return Reference to the set of Unit pointers.
			 */
			const std::set<Unit*>& getUnitsByType(UNITTYPES unittype);

		private:
			/**
			 * Holds all units orderd by UNITTYPES.
			 */
			std::map<UNITTYPES, std::set<Unit*>*> units;
	};
}

#endif
