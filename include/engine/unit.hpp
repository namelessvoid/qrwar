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

	int getAttackRange() const;
	bool isTargetWithinAttackRange(const Coordinates& target) const;

	int getHP();
	void setHP(int hp);
	int getMaxHp();
	void setMaxHp(int maxhp);

	void damage(int inflictedDamage);

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
