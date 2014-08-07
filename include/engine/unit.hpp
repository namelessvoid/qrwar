#ifndef QRW_UNIT_HPP
#define QRW_UNIT_HPP

#include <string>
// #include "engine/player.hpp"

#include "engine/coordinates.hpp"

namespace qrw
{
	class Player;
	class Square;
	class Board;
	class Path;

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
			/**
			 * @brief The AttackResult struct to return results of the Unit::attack() method.
			 */
			struct AttackResult
			{
				/**
				 * @brief Hit points the attacker lost.
				 */
				int attackerHPDelta;
				/**
				 * @brief Hit points the defender lost.
				 */
				int defenderHPDelta;
			};

			Unit(UNITTYPES type, int hp, int attack, int defense,
				int range, int movement, Player* player, Board* board);
			~Unit();

			Player* getPlayer() const;
			void setPlayer(Player* player);
			UNITTYPES getType();

			/**
			 * @brief Get unit base attack value.
			 * @return Base attack value set by constructor.
			 */
			int getBaseAttack();

			/**
			 * @brief Get attack value after applying modifiers.
			 * @return Modified attack value.
			 */
			int getModifiedAttack();

			/**
			 * @brief Get unit base defense value.
			 * @return Base defense value set by constructor.
			 */
			int getBaseDefense();

			/**
			 * @brief Get defense value after applying modifiers.
			 * @return Modified defense value.
			 */
			int getModifiedDefense();

			int getRange();
			int getHP();
			void setHP(int hp);
			int getMaxHp();
			void setMaxHp(int maxhp);
			int getMovement();
			int getCurrentMovement();
			void setCurrentMovement(int movement);
			std::string getName();

			static 	std::string UNITNAMES[EUT_NUMBEROFUNITTYPES];

			/**
			 * @brief Get the square on which Unit currently stands.
			 * @return Pointer to Square.
			 */
			Square* getSquare() const;

			/**
			 * @brief Set the Square on which unit currently stands.
			 * @param square The new square.
			 */
			void setSquare(Square* square);

			/**
			 * @brief Check if the unit can move to given destination Coordinates.
			 * @param destination Coordinates of the destination.
			 * @return Path that leads to destination or nullptr if destination is unreachable.
			 */
			Path* canMoveTo(const Coordinates& destination);

			/**
			 * @brief Move the unit to the given destination.
			 * @param destination Coordinates of the destination.
			 * @return True if movement was successful.
			 */
			bool moveTo(const Coordinates& destination);

			/**
			 * @brief Check if the Unit can attack the given enemy.
			 * @param enemy Enemy Unit to be attacket
			 * @return True if enemy Unit can be attacked.
			 */
			bool canAttack(const Unit* const enemy);

			/**
			 * @brief Executes an attack (includes counter attack).
			 * @param enemy The enemy which is attacked.
			 * @param allowCounterAttack States if enemy is able to do a counter attack (default).
			 */
			AttackResult attack(Unit* enemy, bool allowCounterAttack = true);

	private:
			UNITTYPES type;
			int attackvalue;
			int defensevalue;
			int hp;
			int maxhp;
			int range;
			int movement;
			int currentmovement;
			Player* player;

			Square* square;
			Board* board;

	};
}

#endif
