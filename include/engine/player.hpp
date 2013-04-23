#ifndef QRW_PLAYER_HPP
#define QRW_PLAYER_HPP

#include <vector>
#include <string>

#include "engine/unit.hpp"

namespace qrw
{
	class Player
	{
		public:
			Player();
			~Player();

			std::string getName();
			void setName(std::string name);

			/**
			 * @Return A copy of the list of the units of the player.
			 */
			std::vector<Unit*> getUnits();
			void addUnit(Unit* unit);
			int* getNumberOfUnits();
			void clearUnits();

		private:
			std::string name;
			std::vector<Unit*> units;
			int numberofunits[EUT_NUMBEROFUNITTYPES];
	};
}

#endif