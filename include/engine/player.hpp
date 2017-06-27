#ifndef QRW_PLAYER_HPP
#define QRW_PLAYER_HPP

#include <string>
#include <memory>

#include "engine/army.hpp"

namespace qrw
{
	class Player
	{
		public:
			typedef std::shared_ptr<Player> Ptr;

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
			bool isActive() const;

			/**
			 * @brief Set the active state of the player.
			 * @param active The new active state.
			 */
			void setActive(bool active);

			Army& getArmy();

	private:
			std::string _name;
			int _id;

			bool _active;

			Army _army;
	};
}

#endif
