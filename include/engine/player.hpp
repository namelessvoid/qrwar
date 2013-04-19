#ifndef QRW_PLAYER_HPP
#define QRW_PLAYER_HPP

#include <vector>

#include "engine/unit.hpp"

namespace qrw
{
	class Player
	{
		public:
			Player();
			~Player();

			std::vector<Unit*>& getUnits();

		private:
			std::vector<Unit*> units;

	};
}

#endif