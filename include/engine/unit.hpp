#ifndef QRW_UNIT_HPP
#define QRW_UNIT_HPP

#include <string>

#include "engine/player.hpp"

namespace qrw
{
	class Unit
	{
		public:
			Unit(std::string name, int attack, int defense,
				int range, Player* player);
			~Unit();

			Player* getPlayer();

		private:
			std::string name;
			int attack;
			int defense;
			int range;
			Player* player;

	};
}

#endif