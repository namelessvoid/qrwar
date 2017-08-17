#include "game/damagenumber.hpp"

#include "foundation/textcomponent.hpp"
#include "foundation/transformanimationcomponent.hpp"

#include "game/renderlayers.hpp"

namespace qrw
{

DamageNumber::DamageNumber(int inflictedDamage)
{
	m_textComponent = new TextComponent(RENDER_LAYER_BILLBOARD);
	addComponent(m_textComponent);
	m_textComponent->setText("-" + std::to_string(inflictedDamage));
	m_textComponent->setPosition({50, 50});
	m_textComponent->setFillColor(sf::Color::Red);

	TransformAnimationComponent* animation = new TransformAnimationComponent(m_textComponent);
	addComponent(animation);
}

void DamageNumber::setPosition(const sf::Vector2f& position)
{
	m_textComponent->setPosition(position);
}

} // namespace qrw
