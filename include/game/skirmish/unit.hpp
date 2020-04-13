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
#include "game/skirmish/unitability.hpp"

#include "foundation/gameobject.hpp"

namespace qrw
{
class Path;
class SpriteComponent;
class FollowRouteAnimationComponent;

class Unit : public GameObject, public EventHandler
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

	int getCurrentHp() const;
	void setCurrentHp(int hp);
	int getMaxHp() const;

	void damage(int inflictedDamage);

	int getMovement() const;
	int getCurrentMovement() const;
	void setCurrentMovement(int movement);

	const Coordinates& getBoardPosition() const;

	void deploy(const Coordinates& boardPosition);
	void move(const Path& path);

	inline const std::list<UnitAbility*>& getAbilities() const { return specialAbilities_; }
	UnitAbility* updateAbilitiesToTarget(const Coordinates& boardPosition);
	void deactivateAllAbilities();
	bool tryExecuteAbility(const Coordinates& boardPosition);

	bool handleEvent(const IEvent& event) override;

protected:
	SpriteComponent* _sprite;

	void setType(UNITTYPES type) { _type = type; }

	void setMaxHp(int maxhp) { _maxhp = maxhp; }

	void setAttack(int attack) { _attackvalue = attack; }

	void setDefense(int defense) { _defensevalue = defense; }

	void setMaxMovement(int movement) { _movement = movement; }

	void addAbility(UnitAbility* ability);

	virtual void setPlayer(Player::Ptr& player) { _player = player; }

	class UnitMovementAbility* movementAbility_;
	class UnitMeleeAttackAbility* attackAbility_;

private:
	void setBoardPosition_(const Coordinates& boardPosition);

	void setTexture(const sf::Texture* texture);

	UNITTYPES _type;
	int _hp;
	int _maxhp;
	int _attackvalue;
	int _defensevalue;
	int _movement;
	int _currentmovement;
	Player::Ptr _player;

	Coordinates _boardPosition;

	FollowRouteAnimationComponent* followRouteAnimationComponent_;

	std::list<UnitAbility*> specialAbilities_;
};

} // namespace qrw

#endif // QRW_UNIT_HPP
