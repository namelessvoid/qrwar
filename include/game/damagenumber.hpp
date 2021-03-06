#ifndef QRW_DAMAGENUMBER_HPP
#define QRW_DAMAGENUMBER_HPP

#include <SFML/System/Vector2.hpp>

#include "foundation/gameobject.hpp"

namespace qrw
{
class TextComponent;
class TransformAnimationComponent;

class DamageNumber : public GameObject
{
public:
	const SID& getTypeName() const override	{ throw "Not implemented"; }

	DamageNumber();

	void setDamage(int damage);

	virtual void update(float elapsedTimeInSeconds) override;

    void setPosition(const sf::Vector2f& position);

private:
    TextComponent* m_textComponent;

	TransformAnimationComponent* m_animation;
};

} // namespace qrw

#endif // QRW_DAMAGENUMBER_HPP
