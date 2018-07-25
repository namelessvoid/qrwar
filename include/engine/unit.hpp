#ifndef QRW_UNIT_HPP
#define QRW_UNIT_HPP

#include <string>
#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/unittypes.hpp"
#include "engine/board.hpp"
#include "engine/player.hpp"
#include "engine/coordinates.hpp"

#include "foundation/gameobject.hpp"

namespace qrw
{
class Path;
class SpriteComponent;
class FollowRouteAnimationComponent;

class Unit : public GameObject
{
public:
	static Unit* createUnit(UNITTYPES unitType, Player::Ptr player);

	Unit();

	~Unit();

	virtual void onDestroy() override;

	Player::Ptr getPlayer() const;
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

	void damage(int inflictedDamage);

	int getMovement();
	int getCurrentMovement();
	void setCurrentMovement(int movement);
	std::string getName();

	const Coordinates& getPosition() const;

	void setPosition(const Coordinates& position);
	void move(const Path& path);

	static std::string UNITNAMES[EUT_NUMBEROFUNITTYPES];

private:
	void setPosition_(const Coordinates& position);

	void setType(UNITTYPES type) { _type = type; }

	void setMaxHp(int maxhp) { _maxhp = maxhp; }

	void setAttack(int attack) { _attackvalue = attack; }

	void setDefense(int defense) { _defensevalue = defense; }

	void setRange(int range) { _range = range; }

	void setMovement(int movement) { _movement = movement; }

	void setPlayer(Player::Ptr player) { _player = player; }

	void setTexture(const sf::Texture* texture);

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

	Coordinates _position;

	SpriteComponent* _sprite;
	FollowRouteAnimationComponent* followRouteAnimationComponent_;
};

} // namespace qrw

#endif // QRW_UNIT_HPP
