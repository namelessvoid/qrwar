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
			Unit(UNITTYPES type, int hp, int attack, int defense,
				int range, int movement, Player* player);
			~Unit();

			Player* getPlayer();
			void setPlayer(Player* player);
			UNITTYPES getType();
			int getAttack();
			int getDefense();
			int getRange();
			int getHP();
			void setHP(int hp);
			int getMovement();
			int getCurrentMovement();
			void setCurrentMovement(int movement);

			void attack(Unit* enemy);

		private:
			/**
			 * Calculate the result of a battle round as
			 * the number of hitpoints left of the enemy.
			 *
			 * @return: The number of hitpoints the enemy has
			 * left after the battle.
			 */
			int battleHPResult(Unit* enemy);

			UNITTYPES type;
			int attackvalue;
			int defensevalue;
			int hp;
			int range;
			int movement;
			int currentmovement;
			Player* player;

	};
}

#endif