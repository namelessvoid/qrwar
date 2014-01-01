#ifndef QRW_UNIT_HPP
#define QRW_UNIT_HPP

#include <string>
// #include "engine/player.hpp"

namespace qrw
{
	class Player;
	class Square;

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
			int getMaxHp();
			void setMaxHp(int maxhp);
			int getMovement();
			int getCurrentMovement();
			void setCurrentMovement(int movement);
			std::string getName();

			void attack(Unit* enemy, int* attackmods, int* defensemods);

			static 	std::string UNITNAMES[EUT_NUMBEROFUNITTYPES];

		private:
			/**
			 * Calculate the result of a battle round as
			 * the number of hitpoints left of the enemy.
			 *
			 * @return: The number of hitpoints the enemy has
			 * left after the battle.
			 */
			int battleHPResult(Unit* enemy, int attackmod, int defensemod);

			UNITTYPES type;
			int attackvalue;
			int defensevalue;
			int hp;
			int maxhp;
			int range;
			int movement;
			int currentmovement;
			Player* player;

	};
}

#endif
