#ifndef QRW_ARMY_HPP
#define QRW_ARMY_HPP

#include <vector>

#include "engine/unit.hpp"
#include "engine/unitsmap.hpp"

namespace qrw
{
	/**
	 * @brief The army represents a group of units that belong to a player.
	 *
	 * You can add units to an army. When deploying a unit via the engine, Army::deployUnit() is called
	 * to keep track of the deployment state which can be examined via getDeployedUnitCount() or
	 * getDeployedUnits().
	 */
	class Army
	{
		public:
			Army();
			~Army();

			void setMaxSize(int maxsize);

			bool isFull();

			/**
			 * @brief Add unit to the army.
			 *
			 * Adds a new unit to the army (not deployed).
			 * @param unit Pointer to unit that is added.
			 * @return True if units was successfully added, false otherwise.
			 */
			bool addUnit(Unit* unit);

			void deleteAllUnits();

			std::set<Unit*>& getUnitsByType(UNITTYPES unittype);

			/**
			 * @brief Get the number of units in this army separated by UNITTYPES.
			 *
			 * Get the number of units that have been added (addUnit()).
			 * @return Integer array which holds the unit count for each UNITTYPES and has
			 * size UNITTYPES::EUT_NUMBEROFUNITTYPES.
			 * @see UNITTYPES
			 * @see UnitsMap::getTotalUnitCount()
			 */
			int* getUnitCount();

			int getUnitCount(UNITTYPES unittype);

			std::set<Unit*>& getUndeployedUnitsByType(UNITTYPES unittype);

			/**
			 * @brief Marks a unit as deployed.
			 *
			 * This method is called if a unit is deployed. It saves the deployment state so it can be retrieved later.
			 * @param unit Pointer to the unit that is deployed. The unit has to be added via addUnit() first or deployUnit()
			 * does nothing.
			 * @return True if unit could be marked as deployed, false otherwise.
			 */
			bool markUnitAsDeployed(Unit* unit);

			/**
			 * @brief Get the number of deployed units
			 *
			 * Similar to getUnitCount() but counts the number af deployed units.
			 * @return Like getUnitCount() it also returns an array which holds the count of already deployed units per
			 * unit type. The array has size UNITTYPES::EUT_NUMBEROFUNITTYPES.
			 * @see UNITTYPES
			 * @see UnitsMap::getTotalUnitCount()
			 */
			int* getTotalDeployedUnitCount();

			int getDeployedUnitCount(UNITTYPES unittype);

		private:
			int maxsize;

			/**
			 * @brief All units in the army.
			 *
			 * Contains a pointer to all units of which the army consists.
			 */
			UnitsMap units;

			/**
			 * @brief Units that have not been deployed yet.
			 */
			UnitsMap undeployedunits;

			/**
			 * @brief Already deployed units.
			 *
			 * In this vector all units that have been deployed are saved.
			 * If all units have been deployed, it contains the same pointers as
			 * the Army::units vector.
			 */
			UnitsMap deployedunits;
	};
}

#endif