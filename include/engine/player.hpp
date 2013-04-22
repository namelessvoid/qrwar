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
			std::vector<Unit*>& getUnits();

		private:
			std::string name;
			std::vector<Unit*> units;
	};
}

#endif