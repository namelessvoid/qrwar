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
    DamageNumber(int inflictedDamage);

	virtual void update() override;

    void setPosition(const sf::Vector2f& position);

private:
    TextComponent* m_textComponent;

	TransformAnimationComponent* m_animation;
};

} // namespace qrw

#endif // QRW_DAMAGENUMBER_HPP
