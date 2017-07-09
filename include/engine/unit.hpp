#ifndef QRW_UNIT_HPP
#define QRW_UNIT_HPP

#include <string>
#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/unittypes.hpp"
#include "engine/board.hpp"
#include "engine/player.hpp"
#include "engine/coordinates.hpp"

namespace qrw
{
class Path;

class Unit : public sf::RectangleShape
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

	/**
	 * @brief Shared pointer to a Unit.
	 */
	typedef std::shared_ptr<Unit> Ptr;

	static Ptr createUnit(UNITTYPES unitType, Player::Ptr player, Board::Ptr board);

	~Unit();

	Player::Ptr getPlayer() const;
	void setPlayer(Player::Ptr _player);
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

	const Coordinates& getPosition() const;

	void setPosition(const Coordinates& position);

	static std::string UNITNAMES[EUT_NUMBEROFUNITTYPES];

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
	 * @brief Attack an enemy Unit which then counter attacks.
	 * @param enemy The enemy which is attacked.
	 */
	AttackResult attack(Ptr enemy);

private:
	/**
	 * @brief Private Unit constructor.
	 * @param type The type of the unit, i.e. one of UNITTYPES.
	 * @param hp Max HP of the unit.
	 * @param attack Base attack of the unit.
	 * @param defense Base defense of the unit.
	 * @param range Base range of the unit.
	 * @param movement Base movement of the unit.
	 * @param player The player owning the unit.
	 * @param board Reference to the board on which the unit should be placed.
	 */
	Unit(UNITTYPES type, int hp, int attack, int defense,
		int range, int movement, Player::Ptr player, Board::Ptr board,
		 const sf::Texture* texture);

	/**
	 * @brief Executes the actual attack of the Unit against the enemy.
	 * @param The enemy that is being attacked.
	 * @return The damage dealt.
	 */
	int doAttack(Ptr enemy);

	UNITTYPES _type;
	int _hp;
	int _maxhp;
	int _attackvalue;
	int _defensevalue;
	int _range;
	int _movement;
	int _currentmovement;
	Player::Ptr _player;

	static const float _dimension;

	Board::Ptr _board;
//	Square* _square;
	Coordinates _position;
};

} // namespace qrw

#endif // QRW_UNIT_HPP
