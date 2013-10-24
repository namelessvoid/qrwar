#ifndef QRW_PLAYER_HPP
#define QRW_PLAYER_HPP

#include <vector>
#include <string>

#include "engine/unit.hpp"
#include "engine/army.hpp"

namespace qrw
{
	class Player
	{
		public:
			Player();
			~Player();

			std::string getName();
			void setName(std::string name);
			int getId();
			void setId(int id);

			Army& getArmy();

		private:
			std::string name;
			int id;

			Army army;
	};
}

#endif