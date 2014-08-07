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

			/**
			 * @brief Return if player is active or not.
			 * @return True if player is active otherwise false.
			 */
			bool getActive() const;

			/**
			 * @brief Set the active state of the player.
			 * @param active The new active state.
			 */
			void setActive(bool active);

			Army& getArmy();

	private:
			std::string name;
			int id;

			bool active;

			Army army;
	};
}

#endif
