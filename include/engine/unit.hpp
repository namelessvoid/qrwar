#ifndef QRW_UNIT_HPP
#define QRW_UNIT_HPP

#include <string>

#include "engine/unittypes.hpp"

namespace qrw
{
	class Player;
	class Square;
	class Board;
	class Coordinates;
	class Path;

	class Unit
	{
		public:
			/**
			 * @brief The AttackResult struct to return results of the Unit::attack() method.
			 */
			struct AttackResult
			{
				/**
				 * @brief True if the attack could be performed or false if one requirement (e.g. not the active player)
				 * was not fullfilled.
				 */
				bool attackPerformed = false;

				/**
				 * @brief Hit points the attacker lost.
				 */
				int attackerHPDelta = 0;
				/**
				 * @brief Hit points the defender lost.
				 */
				int defenderHPDelta = 0;
			};

			Unit(UNITTYPES _type, int _hp, int attack, int defense,
				int _range, int _movement, Player* _player, Board* _board);
			~Unit();

			Player* getPlayer() const;
			void setPlayer(Player* _player);
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
			void setHP(int _hp);
			int getMaxHp();
			void setMaxHp(int _maxhp);
			int getMovement();
			int getCurrentMovement();
			void setCurrentMovement(int _movement);
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
			void setSquare(Square* _square);

			/**
			 * @brief Removes the unit from the board.
			 */
			void removeFromBoard();

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
			 * @brief Attack an enemy Unit which then counter attacks.
			 * @param enemy The enemy which is attacked.
			 */
			AttackResult attack(Unit* enemy);

	private:
			/**
			 * @brief Executes the actual attack of the Unit against the enemy.
			 * @param The enemy that is being attacked.
			 * @return The damage dealt.
			 */
			int doAttack(Unit* enemy);

			UNITTYPES _type;
			int _hp;
			int _maxhp;
			int _attackvalue;
			int _defensevalue;
			int _range;
			int _movement;
			int _currentmovement;
			Player* _player;

			Board* _board;
			Square* _square;
	};
}

#endif
