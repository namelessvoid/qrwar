#ifndef QRW_UNIT_HPP
#define QRW_UNIT_HPP

#include <string>
// #include "engine/player.hpp"

namespace qrw
{
	class Player;
	
	enum UNITTYPES
	{
		EUT_SWORDMAN,
		EUT_ARCHER,
		EUT_SPEARMAN,
		EUT_NUMBEROFUNITTYPES
	};

	class Unit
	{
		public:
			Unit(UNITTYPES type, int attack, int defense,
				int range, int movement, Player* player);
			~Unit();

			Player* getPlayer();
			UNITTYPES getType();
			int getAttack();
			int getDefense();
			int getRange();
			int getHP();
			// void setHitpoints();
			int getMovement();
			int getCurrentMovement();
			void setCurrentMovement(int movement);

		private:
			UNITTYPES type;
			int attack;
			int defense;
			int hp;
			int range;
			int movement;
			int currentmovement;
			Player* player;

	};
}

#endif