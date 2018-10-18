#ifndef QRW_UNIT_HPP
#define QRW_UNIT_HPP

#include <string>
#include <memory>
#include <list>

#include <SFML/Graphics/RectangleShape.hpp>

#include "unittypes.hpp"
#include "engine/board.hpp"
#include "engine/player.hpp"
#include "game/skirmish/coordinates.hpp"
#include "game/skirmish/unitspecialability.hpp"

#include "foundation/gameobject.hpp"

namespace qrw
{
class Path;
class SpriteComponent;
class FollowRouteAnimationComponent;

class Unit : public GameObject
{
public:
	friend class UnitFactory;

	const SID& getTypeName() const override { throw "Not implemented"; }

	Unit();

	virtual ~Unit() = default;

	void onDestroy() override;

	Player::Ptr getPlayer() const;
	UNITTYPES getType() const;

	/**
	 * @brief Get unit base attack value.
	 * @return Base attack value set by constructor.
	 */
	int getBaseAttack() const;

	/**
	 * @brief Get attack value after applying modifiers.
	 * @return Modified attack value.
	 */
	int getModifiedAttack();

	/**
	 * @brief Get unit base defense value.
	 * @return Base defense value set by constructor.
	 */
	int getBaseDefense() const;

	/**
	 * @brief Get defense value after applying modifiers.
	 * @return Modified defense value.
	 */
	int getModifiedDefense();

	int getAttackRange() const;
	bool isTargetWithinAttackRange(const Coordinates& target) const;

	int getHP() const;
	void setHP(int hp);
	int getMaxHp() const;

	void damage(int inflictedDamage);

	int getMovement() const;
	int getCurrentMovement() const;
	void setCurrentMovement(int movement);

	const Coordinates& getPosition() const;

	void setPosition(const Coordinates& position);
	void move(const Path& path);

	inline const std::list<UnitSpecialAbility*>& getSpecialAbilities() const { return specialAbilities_; }
	UnitSpecialAbility* updateAbilitiesToTarget(const Coordinates& boardPosition);
	void deactivateAllAbilities();
	bool tryExecuteAbility(const Coordinates& boardPosition);

protected:
	SpriteComponent* _sprite;

	void setType(UNITTYPES type) { _type = type; }

	void setMaxHp(int maxhp) { _maxhp = maxhp; }

	void setAttack(int attack) { _attackvalue = attack; }

	void setDefense(int defense) { _defensevalue = defense; }

	void setRange(int range) { _range = range; }

	void setMovement(int movement) { _movement = movement; }

	void addSpecialAbility(UnitSpecialAbility* ability);

private:
	void setPosition_(const Coordinates& position);

	void setPlayer(Player::Ptr& player) { _player = player; }

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

	Coordinates _position;

	FollowRouteAnimationComponent* followRouteAnimationComponent_;
	class UnitMovementAbility* movementAbility_;
	class UnitAttackAbility* attackAbility_;

	std::list<UnitSpecialAbility*> specialAbilities_;
};

} // namespace qrw

#endif // QRW_UNIT_HPP
